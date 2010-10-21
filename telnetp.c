#include <stdlib.h>
#include <stdio.h>

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

# define LOG(...) { fprintf(stdout, "%s:%d -> ", __FILE__, __LINE__); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n"); }

#ifndef TRUE
# define TRUE 1
#endif
#ifndef FALSE
# define FALSE 0
#endif

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

struct {
    unsigned char command;
    char name[];
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

struct telnetp
{
    /* the TCP socket */
    int tcp_socket;

    /* the file descripter set used for poll */
    struct pollfd fd;

    /* incoming buffer */
    char *incoming_buffer;
    int incoming_buffer_i;
    size_t incoming_buffer_c;
};

struct telnetp *
telnet_connect(char *hostname, unsigned short port)
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

    /* connect */
    struct hostent *host = gethostbyname(hostname);
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    memcpy(&(sockaddr.sin_addr.s_addr), host->h_addr, host->h_length);
    sockaddr.sin_port = htons(port);
    if( connect(t->tcp_socket, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) == -1 ) {
        LOG("connect problem: %d", errno);
        telnet_close(t);
        return NULL;
    }

    /* set up buffers */
    t->incoming_buffer_c = 0;
    t->incoming_buffer = memory_grow_to_size(t->incoming_buffer,
                                             &t->incoming_buffer_c,
                                             4);

    return t;
}

static void
process_commands(struct telnetp *t)
{
    /* stub */
}

static void
collect_incoming(struct telnetp *t)
{    
    t->incoming_buffer_i = 0;

    char done = FALSE;
    while(!done) 
    {
        t->fd.events = POLLIN;
        int ret = poll(&t->fd, 1, 0);
        switch(ret) {
        case 0:
            done = TRUE;
            break;
        case -1:
            /* error occurred */
            LOG("problem polling incoming data: %d", errno);
            t->incoming_buffer_i = -1;
            break;
        }
        
        if(ret > 0)
        {
            /* file descriptor should be open for reading assume data
             * is available at this point */
            ssize_t new_len = recv(t->tcp_socket,
                                   t->incoming_buffer + t->incoming_buffer_i, 
                                   t->incoming_buffer_c - t->incoming_buffer_i,
                                   0);
                       
            /* allocate more if we are up against the limit */
            if(new_len == t->incoming_buffer_c - t->incoming_buffer_i)
            {
                LOG("allocating more space for incoming buffer");
                
                
                t->incoming_buffer = memory_grow_to_size(t->incoming_buffer,
                                                         &t->incoming_buffer_c,
                                                         t->incoming_buffer_c * 2);
            }

            t->incoming_buffer_i += new_len;
        }
    }
}

int
telnet_process_incoming(struct telnetp *t, char **buffer)
{
    /* collect raw data */
    collect_incoming(t);

    /* process any commands present in the input */
    process_commands(t);

    /* return data */
    *buffer = t->incoming_buffer;
    return t->incoming_buffer_i;
}

void
telnet_close(struct telnetp *t)
{
    /* close tcp socket */
    if( close(t->tcp_socket) == -1 )
        LOG("socket close problem: %d", errno);

    free(t->incoming_buffer);    
    free(t);
}
