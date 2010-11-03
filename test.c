#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "telnetp.h"

static void
telnet_callback(int type, void *data)
{
    switch(type) {
    case TC_LINE_FEED:
        printf("\n");
        break;
    case TC_CARRIAGE_RETURN:
        printf("\r");
        break;
    case TC_ASCII: {
        struct ascii_callback *ac_data = data;
        printf("%c", ac_data->c);
        break;
    }
    }
}

static void
rec_echo_command(int type)
{
    printf("server says it will echo: %d\n", type);
    printf("stop echoing for now\n");
}

int
main(int argc, char *argv[])
{
    //struct telnetp *tn = telnetp_connect("oak", 23, telnet_callback);
    //struct telnetp *tn = telnetp_connect("aardmud.org", 4000, telnet_callback);
    struct telnetp *tn = telnetp_connect("realmsofdespair.com", 4000, telnet_callback);

    if(!tn) {
        printf("problem connecting\n");
        return 1;
    }

    telnetp_enable_option(tn, TO_ECHO, true, rec_echo_command);
    telnetp_enable_option(tn, TO_SUPRESS_GO_AHEAD, true, NULL);
    telnetp_enable_option(tn, TO_COMPRESS2, true, NULL);

    int i=0;
    for(i=0; i<3; i++)
    {
        sleep(1);

        telnetp_process_incoming(tn);
        
        char tmp[512];
        scanf("%s", tmp);
        telnetp_send_line(tn, tmp, strlen(tmp));

        sleep(1);
    }

    telnetp_close(tn);

    return 0;
}
