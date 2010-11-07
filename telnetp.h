#ifndef __TELNETP_H__
#define __TELNETP_H__

#include "utils.h"
#include "ansi_p_codes.h"

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

struct ansi_callback_1arg
{
    int arg;
};

struct ansi_callback_2arg
{
    int arg1, arg2;
};

/* ANSI SGR OPTIONS */

#define ASGR_RESET             0
#define ASGR_BRIGHT            1
#define ASGR_FAINT             2
#define ASGR_ITALIC_ON         3
#define ASGR_UNDERLINE_SING    4
#define ASGR_BLINK_SLOW        5
#define ASGR_BLINK_RAPID       6
#define ASGR_IMAGE_NEGATIVE    7
#define ASGR_CONCEAL           8
#define ASGR_CROSSED_OUT       9
#define ASGR_DEFAULT_FONT     10
#define ASGR_ALT_FONT1        11
#define ASGR_ALT_FONT2        12
#define ASGR_ALT_FONT3        13
#define ASGR_ALT_FONT4        14
#define ASGR_ALT_FONT5        15
#define ASGR_ALT_FONT6        16
#define ASGR_ALT_FONT7        17
#define ASGR_ALT_FONT8        18
#define ASGR_ALT_FONT9        19
#define ASGR_FRAKTUR          20
#define ASGR_UNDERLINE_DOUB   21
#define ASGR_NORMAL_COLOR     22
#define ASGR_NOT_ITALIC       23
#define ASGR_UNDERLINE_NONE   24
#define ASGR_BLINK_OFF        25
#define ASGR_IMAGE_POSITIVE   27
#define ASGR_REVEAL           28
#define ASGR_NOT_CROSSED_OUT  29
#define ASGR_TEXT_COLOR_1     30
#define ASGR_TEXT_COLOR_2     31
#define ASGR_TEXT_COLOR_3     32
#define ASGR_TEXT_COLOR_4     33
#define ASGR_TEXT_COLOR_5     34
#define ASGR_TEXT_COLOR_6     35
#define ASGR_TEXT_COLOR_7     36
#define ASGR_TEXT_COLOR_8     37
#define ASGR_DEF_TEXT_COLOR   39
#define ASGR_BG_COLOR_1       40
#define ASGR_BG_COLOR_2       41
#define ASGR_BG_COLOR_3       42
#define ASGR_BG_COLOR_4       43
#define ASGR_BG_COLOR_5       44
#define ASGR_BG_COLOR_6       45
#define ASGR_BG_COLOR_7       46
#define ASGR_BG_COLOR_8       47
#define ASGR_DEF_BG_COLOR     49
#define ASGR_FRAMED           51
#define ASGR_ENCIRCLED        52
#define ASGR_OVERLINED        53
#define ASGR_NOT_FRAME_ENCIR  54
#define ASGR_NOT_OVERLINED    55
#define ASGR_ID_UNDERLINE     60
#define ASGR_ID_DBL_UNDERLINE 61
#define ASGR_ID_OVERLINE      62
#define ASGR_ID_DBL_OVERLINE  63
#define ASGR_ID_STRESS_MARK   64
#define ASGR_FG_COLOR_HIGH1   90
#define ASGR_FG_COLOR_HIGH2   91
#define ASGR_FG_COLOR_HIGH3   92
#define ASGR_FG_COLOR_HIGH4   93
#define ASGR_FG_COLOR_HIGH5   94
#define ASGR_FG_COLOR_HIGH6   95
#define ASGR_FG_COLOR_HIGH7   96
#define ASGR_FG_COLOR_HIGH8   97
#define ASGR_FG_COLOR_HIGH9   98
#define ASGR_FG_COLOR_HIGH10  99
#define ASGR_BG_COLOR_HIGH1  100
#define ASGR_BG_COLOR_HIGH2  101
#define ASGR_BG_COLOR_HIGH3  102
#define ASGR_BG_COLOR_HIGH4  103
#define ASGR_BG_COLOR_HIGH5  104
#define ASGR_BG_COLOR_HIGH6  105
#define ASGR_BG_COLOR_HIGH7  106
#define ASGR_BG_COLOR_HIGH8  107
#define ASGR_BG_COLOR_HIGH9  108
#define ASGR_BG_COLOR_HIGH10 109


#define ASGR_COLOR1_NORMAL   "#000000"
#define ASGR_COLOR2_NORMAL   "#CD0000"
#define ASGR_COLOR3_NORMAL   "#00CD00"
#define ASGR_COLOR4_NORMAL   "#CDCD00"
#define ASGR_COLOR5_NORMAL   "#0000EE"
#define ASGR_COLOR6_NORMAL   "#CD00CD"
#define ASGR_COLOR7_NORMAL   "#00CDCD"
#define ASGR_COLOR8_NORMAL   "#E5E5E5"
#define ASGR_COLOR1_BRIGHT   "#7F7F7F"
#define ASGR_COLOR2_BRIGHT   "#FF0000"
#define ASGR_COLOR3_BRIGHT   "#00FF00"
#define ASGR_COLOR4_BRIGHT   "#FFFF00"
#define ASGR_COLOR5_BRIGHT   "#5C5CFF"
#define ASGR_COLOR6_BRIGHT   "#FF00FF"
#define ASGR_COLOR7_BRIGHT   "#00FFFF"
#define ASGR_COLOR8_BRIGHT   "#00FFFF"

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
    TC_BREAK,

    /* ANSI escape codes */
    TC_ANSI_CURSOR_UP,
    TC_ANSI_CURSOR_DOWN,
    TC_ANSI_CURSOR_FORWARD,
    TC_ANSI_CURSOR_BACK,
    TC_ANSI_CURSOR_NEXT_LINE,
    TC_ANSI_CURSOR_PREV_LINE,
    TC_ANSI_CURSOR_HORZ_ABS,
    TC_ANSI_CURSOR_POS,
    TC_ANSI_ERASE_DATA,
    TC_ANSI_ERASE_IN_LINE,
    TC_ANSI_SCROLL_UP,
    TC_ANSI_SCROLL_DOWN,
    TC_ANSI_HOR_AND_VER_POS,
    TC_ANSI_SAVE_CUR_POS,
    TC_ANSI_REST_CUR_POS,
    TC_ANSI_DEV_STAT_REP,
    TC_ANSI_HIDE_CURS,
    TC_ANSI_SHOW_CURS,
    TC_ANSI_SGR,
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
