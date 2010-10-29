#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <poll.h>

#include <zlib.h>

#include "telnetp.h"
#include "utils.h"

#define _DEBUG

#ifdef _DEBUG
# define LOG(...) { fprintf(stdout, "%s:%d -> ", __FILE__, __LINE__); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n"); }
#else
# define LOG(...) {}
#endif

/* implementation of RFC 854 */

#define DEFAULT_INCOMING_BUFFER_SIZE          4096

/* printer commands */

#define NUL                     0
#define LF                     10
#define CR                     13
#define BEL                     7
#define BS                      8
#define HT                      9
#define VT                     11
#define FF                     12

/* telnet protocol commands */

#define SE                    240
#define NOP                   241
#define DM                    242
#define BRK                   243
#define IP                    244
#define AO                    245
#define AYT                   246
#define EC                    247
#define EL                    248
#define GA                    249
#define SB                    250
#define WILL                  251
#define WONT                  252
#define DO                    253
#define DONT                  254
#define IAC                   255

/* telnet options */
#define ECHO                       1 /* RFC857 */
#define SUPPRESS_GO_AHEAD          3 /* RFC858 */
#define COMPRESS                  85 /* MCCP */
#define COMPRESS2                 86 /* MCCP */

struct telnetp
{
    /* the TCP socket */
    int tcp_socket;

    /* the file descripter set used for poll */
    struct pollfd fd;

    /* callbacks to client */
    struct telnetp_cbs *callbacks;

    /* compression */
    char mccp_compressed;
    z_stream mccp_zstream;

    struct {
        /* incoming buffer */
        
        unsigned char *buffer;
        int i;                  /* amount of data in buffer */
        size_t c;               /* capacity of buffer */
        int p;                  /* next byte to work with */
    } in;

#define O_YES          1
#define O_NO           2
#define O_WANTYES      3
#define O_WANTNO       4
    
    /* configuration options */
    struct {
        char user_enabled;      /* whether the user wants it enabled */
        int us, him;            /* our state and his state */
        void *data;             /* possible callback or other user
                                 * data, command specific */
    } config[TO_NUM_OPTIONS];
};

static Bytef *zlib_buffer = NULL;
static size_t zlib_buffer_c = 0;

static void
collect_incoming(struct telnetp *t)
{    
    t->in.i = t->in.p = 0;

    /* check if data available on socket */
    int ret = poll(&t->fd, 1, 0);
    switch(ret) {
    case 0: return;
    case -1:
        /* error occurred */
        LOG("problem polling incoming data: %d", errno);
        t->in.i = -1;
        return;
    }
    
    if(ret > 0)
    {
        /* file descriptor should be open for reading - assume data is
         * available at this point */
        if(t->mccp_compressed)
        {
            /* compressed stream, first decompress, and then copy into
             * in buffer */
            ssize_t len = recv(t->tcp_socket, zlib_buffer, zlib_buffer_c, 0);

            /* initialize zstream properties */
            t->mccp_zstream.next_in = zlib_buffer;
            t->mccp_zstream.avail_in = len;
            t->mccp_zstream.next_out = t->in.buffer;
            t->mccp_zstream.avail_out = t->in.c;
            t->mccp_zstream.total_out = 0;

            int ret2 = Z_OK;
            do {
                if(ret2 == Z_BUF_ERROR)
                {
                    t->in.buffer = memory_grow_to_size(t->in.buffer, &t->in.c, t->in.c * 2);
                    t->mccp_zstream.next_in = zlib_buffer;
                    t->mccp_zstream.avail_in = len;
                    t->mccp_zstream.next_out = t->in.buffer;
                    t->mccp_zstream.avail_out = t->in.c;
                    t->mccp_zstream.total_out = 0;
                }
                ret2 = inflate(&t->mccp_zstream, Z_SYNC_FLUSH);
            } while(ret2 == Z_BUF_ERROR);
    
            /* one final check */
            if(ret2 != Z_OK) LOG("fatal error in input stream!!");
            
            t->in.i = t->mccp_zstream.total_out;
        } else {
            /* regular uncompressed stream */
            ssize_t len = recv(t->tcp_socket, t->in.buffer, t->in.c, 0);
            
            t->in.i = len;
        }
    }
}

void
uncompress_remaining(struct telnetp *t)
{
    /* need to uncompress the remaining bytes in the incoming buffer
     * then recopy them back into the buffer itself */

    int remaining = t->in.i - t->in.p;

    if(zlib_buffer_c == 0)
    {
        /* initialize buffer if needed */
        zlib_buffer = malloc(sizeof(*zlib_buffer) * DEFAULT_INCOMING_BUFFER_SIZE);
        zlib_buffer_c = DEFAULT_INCOMING_BUFFER_SIZE;                
    }

    memcpy(zlib_buffer, &t->in.buffer[t->in.p], remaining);

    /* initialize zstream properties */
    t->mccp_zstream.next_in = zlib_buffer;
    t->mccp_zstream.avail_in = remaining;
    t->mccp_zstream.next_out = t->in.buffer;
    t->mccp_zstream.avail_out = t->in.c;
    t->mccp_zstream.zalloc = Z_NULL;
    t->mccp_zstream.zfree = Z_NULL;
    t->mccp_zstream.opaque = Z_NULL;
    t->mccp_zstream.total_out = 0;

    int ret2 = inflateInit(&t->mccp_zstream);
    if(ret2 != Z_OK) LOG("problem initializing inflate");
            
    ret2 = Z_OK;
    do {
        if(ret2 == Z_BUF_ERROR)
        {
            t->in.buffer = memory_grow_to_size(t->in.buffer, &t->in.c, t->in.c * 2);
            t->mccp_zstream.next_in = zlib_buffer;
            t->mccp_zstream.avail_in = remaining;
            t->mccp_zstream.next_out = t->in.buffer;
            t->mccp_zstream.avail_out = t->in.c;
            t->mccp_zstream.total_out = 0;
        }
        ret2 = inflate(&t->mccp_zstream, Z_SYNC_FLUSH);
    } while(ret2 == Z_BUF_ERROR);
    
    /* one final check */
    if(ret2 != Z_OK) LOG("fatal error in input stream!!");
    
    t->in.i = t->mccp_zstream.total_out;
    t->in.p = 0;
}

short
get_next_byte(struct telnetp *t)
{
    /* This function should be called to retrieve the next available
     * byte on the incoming socket. If no data is available then -1
     * will be returned. */

    if(t->in.i == t->in.p)
    {
        /* hit the end so grab more data from the socket */
        collect_incoming(t);
    }

    if(t->in.i != -1)
    {
        /* valid data to follow */
        //LOG("next char = %d", t->in.buffer[t->in.p]);
        
        return t->in.buffer[t->in.p++];
    }
    else
    {
        LOG("no incoming data where there should be, possibly bad command structure");
        return -1;
    }

    return 0;
}

static int
get_index_of_option(struct telnetp *t, unsigned char c)
{
    switch(c) {
    case COMPRESS: return TO_COMPRESS;
    case COMPRESS2: return TO_COMPRESS2;
    case SUPPRESS_GO_AHEAD: return TO_SUPRESS_GO_AHEAD;
    case ECHO: return TO_ECHO;
    default: return -1;
    }
}

static void
send_response(struct telnetp *t, int type, unsigned char c)
{
    char resp[3] = {IAC, type, c};
    telnetp_send_data(t, resp, 3);
}

static int
handle_will(struct telnetp *t)
{
    int ret = get_next_byte(t);
    if(ret == -1) return -1;
    unsigned char c = ret;
    LOG("recieved WILL for: %d", c);
    int ind = get_index_of_option(t, c);
    if(ind == -1)
    {
        /* unknown option, send DONT */
        LOG("unknown option %d, sending DONT", c);
        send_response(t, DONT, c);
    } else {
        if(t->config[ind].him == O_YES) {
            /* ignore */
        } else if(t->config[ind].him == O_NO) {
            if(t->config[ind].user_enabled == true)
            {
                /* we agree to enable */
                t->config[ind].him = O_YES;
                
                /* special cases */
                switch(ind) {
                case TO_ECHO:
                {
                    void (*cb)(int) = t->config[ind].data;
                    cb(ET_SERVER_WILL_ECHO);
                    break;
                }
                };

                send_response(t, DO, c);
            } else {
                /* we don't want this enabled */
                send_response(t, DONT, c);
            }
        } else if(t->config[ind].him == O_WANTYES) {
            t->config[ind].him = O_YES;
        } else if(t->config[ind].him == O_WANTNO) {
            /* this is an error case */
            t->config[ind].him = O_NO;
        }
    }

    return 0;
}

static int
handle_wont(struct telnetp *t)
{
    int ret = get_next_byte(t);
    if(ret == -1) return -1;
    unsigned char c = ret;
    LOG("recieved WONT for: %d", c);
    int ind = get_index_of_option(t, c);
    if(ind == -1)
    {
        /* unknown option, sending dont */
        LOG("unknown option %d, sending dont", c);
        send_response(t, DONT, c);
    } else {
        if(t->config[ind].him == O_YES) {
            t->config[ind].him = O_NO;
            send_response(t, DONT, c);
        } else if(t->config[ind].him == O_NO) {
            /* ignore */
        } else if(t->config[ind].him == O_WANTYES) {
            t->config[ind].him = O_NO;
        } else if(t->config[ind].him == O_WANTNO) {
            t->config[ind].him = O_NO;
        }
    }

    return 0;
}

static int
handle_do(struct telnetp *t)
{
    int ret = get_next_byte(t);
    if(ret == -1) return -1;
    unsigned char c = ret;
    LOG("recieved DO for: %d", c);
    int ind = get_index_of_option(t, c);
    if(ind == -1)
    {
        /* unknown option, send WONT */
        LOG("unknown option %d, sending WONT", c);
        send_response(t, WONT, c);
    } else {
        if(t->config[ind].us == O_YES) {
            /* ignore */
        } else if(t->config[ind].us == O_NO) {
            if(t->config[ind].user_enabled == true)
            {
                /* we agree to enable */
                t->config[ind].us = O_YES;

                /* special cases */
                switch(ind) {
                case TO_ECHO:
                {
                    void (*cb)(int) = t->config[ind].data;
                    cb(ET_SERVER_DO_ECHO);
                    break;
                }
                };

                send_response(t, WILL, c);
            } else {
                /* we don't want this enabled */
                send_response(t, WONT, c);
            }
        } else if(t->config[ind].us == O_WANTYES) {
            t->config[ind].us = O_YES;
        } else if(t->config[ind].us == O_WANTNO) {
            /* this is an error case */
            t->config[ind].us = O_NO;
        }
    }

    return 0;
}

static int
handle_dont(struct telnetp *t)
{
    int ret = get_next_byte(t);
    if(ret == -1) return -1;
    unsigned char c = ret;
    LOG("recieved DONT for: %d", c);
    int ind = get_index_of_option(t, c);
    if(ind == -1)
    {
        /* unknown option, sending wont */
        LOG("unknown option %d, sending wont", c);
        send_response(t, WONT, c);
    } else {
        if(t->config[ind].us == O_YES) {
            t->config[ind].us = O_NO;
            send_response(t, WONT, c);
        } else if(t->config[ind].us == O_NO) {
            /* ignore */
        } else if(t->config[ind].us == O_WANTYES) {
            t->config[ind].us = O_NO;
        } else if(t->config[ind].us == O_WANTNO) {
            t->config[ind].us = O_NO;
        }
    }

    return 0;
}

static int
handle_subneg_begin(struct telnetp *t)
{
    int ret = get_next_byte(t);
    if(ret == -1) return -1;
    unsigned char c = ret;
    LOG("recieved SUBNEGOTIATION BEGIN for: %d", c);
    int ind = get_index_of_option(t, c);
    if(ind == -1 || t->config[ind].user_enabled == false)
    {
        LOG("unknown option or option disabled: %d", c);
        return -1;
    }

    switch(c)
    {
    case COMPRESS2:
    {
        /* look for IAC character */
        ret = get_next_byte(t);
        if(ret == -1) return -1;
        c = ret;
        if(c != IAC) {
            LOG("invalid COMPRESS2 subnegotation sequence");
            return -1;
        }
        /* look for SE character */
        ret = get_next_byte(t);
        if(ret == -1) return -1;
        c = ret;
        if(c != SE) {
            LOG("invalid COMPRESS2 subnegotation sequence");
            return -1;
        }
        /* at this point the rest of the stream from the server is
         * compressed */
        t->mccp_compressed = true;
        uncompress_remaining(t);

        /* TODO: currently not checking to disable COMPRESS  */

        break;
    }
    case COMPRESS:
    {
        /* look for WILL character */
        ret = get_next_byte(t);
        if(ret == -1) return -1;
        c = ret;
        if(c != WILL) {
            LOG("invalid COMPRESS subnegotation sequence");
            return -1;
        }
        /* look for SE character */
        ret = get_next_byte(t);
        if(ret == -1) return -1;
        c = ret;
        if(c != SE) {
            LOG("invalid COMPRESS subnegotation sequence");
            return -1;
        }
        /* at this point the rest of the stream from the server is
         * compressed */
        t->mccp_compressed = true;
        uncompress_remaining(t);
        break;
    }
    default:
        LOG("unknown subnegotiation option");
        return -1;
    }
    
    return 0;
}

static int
handle_subneg_end(struct telnetp *t)
{
    int ret = get_next_byte(t);
    if(ret == -1) return -1;
    unsigned char c = ret;
    LOG("recieved SUBNEGOTIATION END for: %d", c);

    return 0;
}

static int
process_option(struct telnetp *t)
{
    short ret = get_next_byte(t);
    if(ret == -1) return -1;

    unsigned char c = ret;
    switch(c)
    {
    case NOP:
        break;
    case DM:
    case BRK:
    case IP:
    case AO:
    case GA:
        /* TODO: work on these */
        break;
    case EC:
        /* erase character */
        if(t->callbacks && t->callbacks->erase_char_fn)
            t->callbacks->erase_char_fn();
        break;
    case EL:
        /* erase line */
        if(t->callbacks && t->callbacks->erase_line_fn)
            t->callbacks->erase_line_fn();
        break;
    case AYT:
        /* XXX: doesn't seem clear to me what to do with this? */
        break;
    case SE:
        ret = handle_subneg_end(t);
        break;
    case SB:
        ret = handle_subneg_begin(t);
        break;
    case WILL:
        ret = handle_will(t);
        break;
    case WONT:
        ret = handle_wont(t);
        break;
    case DO:
        ret = handle_do(t);
        break;
    case DONT:
        ret = handle_dont(t);
        break;        
    default:
        LOG("unknown telnet option encountered: %d", c);

        return -1;
    }

    if(ret == -1) return -1;

    return 0;
}

static int
process_char(struct telnetp *t, unsigned char c)
{
    if(c >= 32 && c <= 126)
    {
        /* if in the "printable" characters then send the ascii
         * character */
        
        if(t->callbacks && t->callbacks->ascii_fn)
            t->callbacks->ascii_fn(c);
        return 0;
    }

    switch(c)
    {
    case NUL:
        if(t->callbacks && t->callbacks->null_fn)
            t->callbacks->null_fn();
        break;
    case LF:
        if(t->callbacks && t->callbacks->line_feed_fn)
            t->callbacks->line_feed_fn();
        break;
    case CR:
        if(t->callbacks && t->callbacks->carriage_return_fn)
            t->callbacks->carriage_return_fn();
        break;
    case BEL:
        if(t->callbacks && t->callbacks->bell_fn)
            t->callbacks->bell_fn();
        break;
    case BS:
        if(t->callbacks && t->callbacks->backspace_fn)
            t->callbacks->backspace_fn();
        break;
    case HT:
        if(t->callbacks && t->callbacks->horizontal_tab_fn)
            t->callbacks->horizontal_tab_fn();
        break;
    case VT:
        if(t->callbacks && t->callbacks->vertical_tab_fn)
            t->callbacks->vertical_tab_fn();
        break;
    case FF:
        if(t->callbacks && t->callbacks->form_feed_fn)
            t->callbacks->form_feed_fn();
        break;
    case IAC:
    {
        /* process telnet option */
        if( process_option(t) == -1 )
            return -1;
        
        break;
    }
    default:
        LOG("unknown character encountered: %d", c);
        
        //return -1;
        break;
    }

    return 0;
}

static void
process_buffer(struct telnetp *t)
{
    while(t->in.p < t->in.i)
    {
        /* still data remaining to be processed in this cycle */
        
        short ret = get_next_byte(t);
        if(ret == -1) return;
        
        if( process_char(t, (unsigned char)ret) == -1 )
            return;
    }
}

void
telnetp_process_incoming(struct telnetp *t)
{
    /* *buffer will be filled with the most recent printer data from
     * the connection */
    collect_incoming(t);

    /* process the incoming buffer */
    process_buffer(t);
}

struct telnetp *
telnetp_connect(char *hostname,
                unsigned short port,
                struct telnetp_cbs *cbs)
{
    struct telnetp *t = malloc(sizeof(*t));

    /* create socket */
    t->tcp_socket = socket(PF_INET, SOCK_STREAM, 0);
    if(t->tcp_socket == -1) {
        LOG("socket creation problem: %d", errno);
        free(t);
        return NULL;
    }

    t->fd.fd = t->tcp_socket;
    t->fd.events = POLLIN;

    /* connect */
    struct hostent *host = gethostbyname(hostname);
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    memcpy(&(sockaddr.sin_addr.s_addr), host->h_addr, host->h_length);
    sockaddr.sin_port = htons(port);
    if( connect(t->tcp_socket, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) == -1 ) {
        LOG("connect problem: %d", errno);
        telnetp_close(t);
        return NULL;
    }

    /* set up buffers */
    t->in.c = t->in.i = t->in.p = 0;
    t->in.buffer = memory_grow_to_size(t->in.buffer, &t->in.c, DEFAULT_INCOMING_BUFFER_SIZE);

    /* turn off all options to begin with */
    int i;
    for(i=0; i<TO_NUM_OPTIONS; i++)
    {
        t->config[i].us = O_NO;
        t->config[i].him = O_NO;
    }

    /* turn off compression by default */
    t->mccp_compressed = false;

    /* connect callbacks */
    t->callbacks = cbs;

    return t;
}

void
telnetp_enable_option(struct telnetp *t, unsigned int type, char enabled, void *data)
{
    if(type < TO_NUM_OPTIONS) 
    {
        t->config[type].user_enabled = enabled;
        t->config[type].data = data;
    }
}

void
telnetp_close(struct telnetp *t)
{
    /* close tcp socket */
    if( close(t->tcp_socket) == -1 )
        LOG("socket close problem: %d", errno);

    free(t->in.buffer);    
    free(t);
}

#define MIN(a,b)     ( (a) < (b) ? (a) : (b) )

int
telnetp_send_data(struct telnetp *t, char *data, unsigned int len)
{
    
#ifdef _DEBUG
    LOG(">>> SENDING >>>");
    int i;
    printf("  ");
    for(i=0; i<MIN(len,255); i++)
        printf("%hhx ", data[i]);
    printf("\n");
#endif

    return send(t->tcp_socket, data, len, 0);
}

static char *out_buf = NULL;
static size_t out_buf_c = 0;

int
telnetp_send_line(struct telnetp *t, char *data, unsigned int len)
{
    /* attach line feed and carriage return */
    out_buf = memory_grow_to_size(out_buf, &out_buf_c, len+2);
    memcpy(out_buf, data, len);
    out_buf[len] = LF;
    out_buf[len+1] = CR;
    return telnetp_send_data(t, out_buf, len+2);
}
