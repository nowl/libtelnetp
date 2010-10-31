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

struct telnetp_cbs {
    /* printer callbacks */
    void (*ascii_fn)(char);
    void (*null_fn)(void);
    void (*line_feed_fn)(void);
    void (*carriage_return_fn)(void);
    void (*bell_fn)(void);
    void (*backspace_fn)(void);
    void (*horizontal_tab_fn)(void);
    void (*vertical_tab_fn)(void);
    void (*form_feed_fn)(void);

    /* other telnet specific callbacks */
    void (*erase_line_fn)(void);
    void (*erase_char_fn)(void);
    void (*are_you_there_fn)(void);
    void (*data_mark_fn)(void);
    void (*abort_output_fn)(void);
    void (*go_ahead_fn)(void);
    void (*interrupt_process_fn)(void);
    void (*break_fn)(void);
};

struct telnetp;

struct telnetp *telnetp_connect(char *hostname,
                                unsigned short port,
                                struct telnetp_cbs cbs);
void telnetp_close(struct telnetp *t);

void telnetp_enable_option(struct telnetp *t, unsigned int type, char enabled, void *data);

void telnetp_process_incoming(struct telnetp *t);
int telnetp_send_data(struct telnetp *t, char *data, unsigned int len);
int telnetp_send_line(struct telnetp *t, char *data, unsigned int len);

#endif  /* __TELNETP_H__ */
