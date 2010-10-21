#ifndef __TELNET_H__
#define __TELNET_H__

struct telnetp;

struct telnetp *telnet_connect(char *hostname, unsigned short port);
void telnet_close(struct telnetp *t);

#endif  /* __TELNET_H__ */
