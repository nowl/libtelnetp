#include <stdio.h>

#include "telnetp.h"

int
main(int argc, char *argv[])
{
    printf("testing\n");

    struct telnetp *tn = telnet_connect("oak", 23);
    
    sleep(2);

    telnet_close(tn);

    return 0;
}
