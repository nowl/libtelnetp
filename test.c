#include <stdio.h>

#include "telnetp.h"

int
main(int argc, char *argv[])
{
    struct telnetp *tn = telnet_connect("oak", 23);
    //struct telnetp *tn = telnet_connect("aardmud.org", 4000);

    unsigned char *incoming;
    int incoming_len;

    sleep(1);

    incoming_len = telnet_process_incoming(tn, &incoming);
        
    printf("length = %d\n", incoming_len);
    int i;
    for(i=0; i<incoming_len; i++)
        printf("%hhx ", incoming[i]);
    printf("\n");

    sleep(1);

    telnet_close(tn);

    return 0;
}
