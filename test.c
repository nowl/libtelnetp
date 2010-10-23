#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "telnetp.h"

int
main(int argc, char *argv[])
{
    struct telnetp *tn = telnetp_connect("oak", 23);
    //struct telnetp *tn = telnetp_connect("aardmud.org", 4000);
    //struct telnetp *tn = telnetp_connect("realmsofdespair.com", 4000);

    //telnetp_enable_option(tn, TO_ECHO, true, NULL);

    unsigned char *incoming;
    int incoming_len;

    int i=0;
    for(i=0; i<3; i++)
    {
        sleep(1);

        incoming_len = telnetp_process_incoming(tn, &incoming);
        
        printf("length = %d\n", incoming_len);
        int i;
        for(i=0; i<incoming_len; i++)
            printf("%hhx ", incoming[i]);
        printf("\n");
        for(i=0; i<incoming_len; i++)
            printf("%c", incoming[i]);
        printf("\n");

        char tmp[512];
        scanf("%s", tmp);
        telnetp_send_line(tn, tmp, strlen(tmp));

        sleep(1);
    }

    telnetp_close(tn);

    return 0;
}
