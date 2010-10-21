#include <stdlib.h>
#include <stdio.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

#include "telnetp.h"

# define LOG(...) { fprintf(stdout, "%s:%d -> ", __FILE__, __LINE__); fprintf(stdout, __VA_ARGS__); }

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

struct telnetp {
    int tcp_socket;
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

    return t;
}

void
telnet_close(struct telnetp *t)
{
    /* close tcp socket */
    if( close(t->tcp_socket) == -1 )
        LOG("socket close problem: %d", errno);

    free(t);
}
