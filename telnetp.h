#ifndef __TELNETP_H__
#define __TELNETP_H__

struct telnetp;

struct telnetp *telnetp_connect(char *hostname, unsigned short port);
void telnetp_close(struct telnetp *t);

enum {
    TO_ECHO,
    TO_SUPRESS_GO_AHEAD,
    
    TO_NUM_OPTIONS
};

void telnetp_enable_option(struct telnetp *t, unsigned int type, char enabled, void *callback);

int telnetp_process_incoming(struct telnetp *t, unsigned char **buffer);
int telnetp_send_data(struct telnetp *t, char *data, unsigned int len);
int telnetp_send_line(struct telnetp *t, char *data, unsigned int len);

#endif  /* __TELNETP_H__ */
