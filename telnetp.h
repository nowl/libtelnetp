#ifndef __TELNETP_H__
#define __TELNETP_H__

enum {
    TO_COMPRESS,
    TO_COMPRESS2,
    TO_SUPRESS_GO_AHEAD,
    TO_ECHO,
    
    TO_NUM_OPTIONS
};

enum echo_types
{
    ET_SERVER_WILL_ECHO,
    ET_SERVER_DO_ECHO
};

struct ascii_callback
{
    unsigned char c;
};

enum telnet_callback_types
{
    /* printer callbacks */
    TC_ASCII,
    TC_NULL,
    TC_LINE_FEED,
    TC_CARRIAGE_RETURN,
    TC_BELL,
    TC_BACKSPACE,
    TC_HORIZONTAL_TAB,
    TC_VERTICAL_TAB,
    TC_FORM_FEED,

    /* other telnet specific callbacks */    
    TC_ERASE_LINE,
    TC_ERASE_CHAR,
    TC_ARE_YOU_THERE,
    TC_DATA_MARK,
    TC_ABORT_OUTPUT,
    TC_GO_AHEAD,
    TC_INTERRUPT_PROCESS,
    TC_BREAK
};

struct telnetp;

struct telnetp *telnetp_connect(char *hostname,
                                unsigned short port,
                                void (*callback_func)(int, void *));
void telnetp_close(struct telnetp *t);

void telnetp_enable_option(struct telnetp *t, unsigned int type, char enabled, void *data);

void telnetp_process_incoming(struct telnetp *t);
int telnetp_send_data(struct telnetp *t, char *data, unsigned int len);
int telnetp_send_line(struct telnetp *t, char *data, unsigned int len);

#endif  /* __TELNETP_H__ */
