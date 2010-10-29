#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "telnetp.h"

static void
rec_line_feed()
{
    printf("\n");
}

static void
rec_car_ret()
{
    printf("\r");
}

static void
rec_bell()
{
}

static void
rec_backspace()
{
}

static void
rec_hor_tab()
{
}

static void
rec_vert_tab()
{
}

static void
rec_form_feed()
{
}

static void
rec_erase_line()
{
}

static void
rec_erase_char()
{
}

static void
rec_ascii(char c)
{
    printf("%c", c);
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
    struct telnetp_cbs cbs = {rec_ascii,
                              NULL,
                              rec_line_feed,
                              rec_car_ret,
                              rec_bell,
                              rec_backspace,
                              rec_hor_tab,
                              rec_vert_tab,
                              rec_form_feed,
                              rec_erase_line,
                              rec_erase_char,
                              NULL,
                              NULL,
                              NULL,
                              NULL,
                              NULL,
                              NULL};

    //struct telnetp *tn = telnetp_connect("oak", 23, &cbs);
    struct telnetp *tn = telnetp_connect("aardmud.org", 4000, &cbs);
    //struct telnetp *tn = telnetp_connect("realmsofdespair.com", 4000, &cbs);

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
