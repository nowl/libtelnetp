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

#include "telnetp.h"
#include "utils.h"

#define _DEBUG

#ifdef _DEBUG
# define LOG(...) { fprintf(stdout, "%s:%d -> ", __FILE__, __LINE__); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n"); }
#else
# define LOG(...)
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
#define IAP                   255

/* telnet options */
#define ECHO                      1 /* RFC857 */
#define SUPPRESS_GO_AHEAD         3 /* RFC858 */

static struct {
    unsigned char command;
    char *name;
} com_name[] = {
    /* printer */
    {NUL, "NO OPERATION"},
    {LF, "LINE FEED"},
    {CR, "CARRIAGE RETURN"},
    {BEL, "BELL"},
    {BS, "BACK SPACE"},
    {HT, "HORIZONTAL TAB"},
    {VT, "VERTICAL TAB"},
    {FF, "FORM FEED"},

    /* commands */
    {SE, "SUBNEGOTIATION END"},
    {NOP, "NO OPERATION"},
    {DM, "DATA MARK"},
    {BRK, "BREAK"},
    {IP, "INTERRUPT PROCESS"},
    {AO, "ABORT OUTPUT"},
    {AYT, "ARE YOU THERE"},
    {EC, "ERASE CHARACTER"},
    {EL, "ERASE LINE"},
    {GA, "GO AHEAD"},
    {SB, "SUBNEGOTIATION BEGIN"},
    {WILL, "WILL"},
    {WONT, "WONT"},
    {DO, "DO"},
    {DONT, "DONT"},
    {IAP, "INTERPRET AS COMMAND"}
};

static int com_name_len = sizeof(com_name)/sizeof(com_name[0]);

static char *
search_for_desc(unsigned char com)
{
    int i;
    for(i=0; i<com_name_len; i++)
        if(com_name[i].command == com)
            return com_name[i].name;

    return "UNKNOWN";
}

struct telnetp
{
    /* the TCP socket */
    int tcp_socket;

    /* the file descripter set used for poll */
    struct pollfd fd;

    struct {
        /* incoming buffer */
        
        unsigned char *buffer;
        int i;                  /* amount of data in buffer */
        size_t c;               /* capacity of buffer */
        int p;                  /* next byte to work with */
    } in;

    struct {
        /* incoming cleaned buffer */

        unsigned char *buffer;
        int i;
        size_t c;
    } inc;

#define O_YES          1
#define O_NO           2
#define O_WANTYES      3
#define O_WANTNO       4
    
    /* configuration options */
    struct {
        char user_enabled;      /* whether the user wants it enabled */
        void *callback;         /* the callback for special cases */
        int us, him;            /* our state and his state */
    } config[TO_NUM_OPTIONS];
};

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
        ssize_t len = recv(t->tcp_socket, t->in.buffer, t->in.c, 0);
        
        t->in.i = len;
    }
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
        LOG("next char = %d", t->in.buffer[t->in.p]);
        
        return t->in.buffer[t->in.p++];
    }
    else
    {
        LOG("no incoming data where there should be, possibly bad command structure");
        return -1;
    }

    return 0;
}

static void
add_to_cleaned_buffer(struct telnetp *t, unsigned char c)
{
    if(t->inc.i == t->inc.c)
        t->inc.buffer = memory_grow_to_size(t->inc.buffer,
                                            &t->inc.c,
                                            t->inc.c * 2);
    t->inc.buffer[t->inc.i++] = c;
}

static int
get_index_of_option(struct telnetp *t, unsigned char c)
{
    switch(c) {
    case ECHO: return TO_ECHO;
    case SUPPRESS_GO_AHEAD: return TO_SUPRESS_GO_AHEAD;
    default: return -1;
    }
}

static void
send_response(struct telnetp *t, int type, unsigned char c)
{
    char resp[3] = {IAP, type, c};
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
process_option(struct telnetp *t)
{
    short ret = get_next_byte(t);
    if(ret == -1) return -1;

    unsigned char c = ret;
    switch(c)
    {
    case SE:
    case NOP:
    case DM:
    case BRK:
    case IP:
    case AO:
    case AYT:
    case EC:
    case EL:
    case GA:
    case SB:
        /* TODO: work on these */
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
        /* if in the "printable" characters then add it to the cleaned
         * buffer */
        
        add_to_cleaned_buffer(t, c);
        return 0;
    }

    switch(c)
    {
    case NUL:
    case LF:
    case CR:
    case BEL:
    case BS:
    case HT:
    case VT:
    case FF:
        
        /* if in the special printer characters then also add it to
         * the cleaned buffer */

        add_to_cleaned_buffer(t, c);

        LOG("recieved special printer character: %d (%s)", c, search_for_desc(c));
        break;
    case IAP:
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

static int
process_buffer(struct telnetp *t)
{
    /* this should place telnet printer characters in the cleaned
     * buffer and process other commands as needed */
    
    while(t->in.p < t->in.i)
    {
        /* still data remaining to be processed in this cycle */
        
        short ret = get_next_byte(t);
        if(ret == -1) return -1;
        
        if( process_char(t, (unsigned char)ret) == -1 )
            return -1;
    }

    return 0;
}

int
telnetp_process_incoming(struct telnetp *t, unsigned char **buffer)
{
    /* *buffer will be filled with the most recent printer data from
     * the connection */
    collect_incoming(t);

    /* reset cleaned incoming buffer */
    t->inc.i = 0;

    /* process the incoming buffer */
    if( process_buffer(t) == -1 )
        t->inc.i = -1;

    /* return data */
    *buffer = t->inc.buffer;
    return t->inc.i;
}

struct telnetp *
telnetp_connect(char *hostname, unsigned short port)
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
    t->inc.c = t->inc.i = 0;
    t->inc.buffer = memory_grow_to_size(t->inc.buffer, &t->inc.c, DEFAULT_INCOMING_BUFFER_SIZE);


    /* turn off all options to begin with */
    int i;
    for(i=0; i<TO_NUM_OPTIONS; i++)
    {
        t->config[i].us = O_NO;
        t->config[i].him = O_NO;
    }

    return t;
}

void
telnetp_enable_option(struct telnetp *t, unsigned int type, char enabled, void *callback)
{
    if(type < TO_NUM_OPTIONS)
    {
        t->config[type].user_enabled = enabled;
        t->config[type].callback = callback;
    }
}

void
telnetp_close(struct telnetp *t)
{
    /* close tcp socket */
    if( close(t->tcp_socket) == -1 )
        LOG("socket close problem: %d", errno);

    free(t->in.buffer);    
    free(t->inc.buffer);    
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
static int out_buf_c = 0;

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
