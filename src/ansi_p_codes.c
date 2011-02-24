#include "ansi_p_codes.h"

#define PCODE_CODE_F1                   "0;59"
#define PCODE_CODE_F1_SHIFT             "0;84"
#define PCODE_CODE_F1_CTRL              "0;94"
#define PCODE_CODE_F1_ALT               "0;104"
#define PCODE_CODE_F2                   "0;60"
#define PCODE_CODE_F2_SHIFT             "0;85"
#define PCODE_CODE_F2_CTRL              "0;95"
#define PCODE_CODE_F2_ALT               "0;105"
#define PCODE_CODE_F3                   "0;61"
#define PCODE_CODE_F3_SHIFT             "0;86"
#define PCODE_CODE_F3_CTRL              "0;96"
#define PCODE_CODE_F3_ALT               "0;106"
#define PCODE_CODE_F4                   "0;62"
#define PCODE_CODE_F4_SHIFT             "0;87"
#define PCODE_CODE_F4_CTRL              "0;97"
#define PCODE_CODE_F4_ALT               "0;107"
#define PCODE_CODE_F5                   "0;63"
#define PCODE_CODE_F5_SHIFT             "0;88"
#define PCODE_CODE_F5_CTRL              "0;98"
#define PCODE_CODE_F5_ALT               "0;108"
#define PCODE_CODE_F6                   "0;64"
#define PCODE_CODE_F6_SHIFT             "0;89"
#define PCODE_CODE_F6_CTRL              "0;99"
#define PCODE_CODE_F6_ALT               "0;109"
#define PCODE_CODE_F7                   "0;65"
#define PCODE_CODE_F7_SHIFT             "0;90"
#define PCODE_CODE_F7_CTRL              "0;100"
#define PCODE_CODE_F7_ALT               "0;110"
#define PCODE_CODE_F8                   "0;66"
#define PCODE_CODE_F8_SHIFT             "0;91"
#define PCODE_CODE_F8_CTRL              "0;101"
#define PCODE_CODE_F8_ALT               "0;111"
#define PCODE_CODE_F9                   "0;67"
#define PCODE_CODE_F9_SHIFT             "0;92"
#define PCODE_CODE_F9_CTRL              "0;102"
#define PCODE_CODE_F9_ALT               "0;112"
#define PCODE_CODE_F10                  "0;68"
#define PCODE_CODE_F10_SHIFT            "0;93"
#define PCODE_CODE_F10_CTRL             "0;103"
#define PCODE_CODE_F10_ALT              "0;113"
#define PCODE_CODE_F11                  "0;133"
#define PCODE_CODE_F11_SHIFT            "0;135"
#define PCODE_CODE_F11_CTRL             "0;137"
#define PCODE_CODE_F11_ALT              "0;139"
#define PCODE_CODE_F12                  "0;134"
#define PCODE_CODE_F12_SHIFT            "0;136"
#define PCODE_CODE_F12_CTRL             "0;138"
#define PCODE_CODE_F12_ALT              "0;140"
#define PCODE_CODE_HOME_KP              "0;71"
#define PCODE_CODE_HOME_KP_SHIFT        "55"
#define PCODE_CODE_HOME_KP_CTRL         "0;119"
#define PCODE_CODE_UP_ARROW_KP          "0;72"
#define PCODE_CODE_UP_ARROW_KP_SHIFT    "56"
#define PCODE_CODE_UP_ARROW_KP_CTRL     "0;141"
#define PCODE_CODE_PAGE_UP_KP           "0;73"
#define PCODE_CODE_PAGE_UP_KP_SHIFT     "57"
#define PCODE_CODE_PAGE_UP_KP_CTRL      "0;132"
#define PCODE_CODE_LEFT_ARROW_KP        "0;75"
#define PCODE_CODE_LEFT_ARROW_KP_SHIFT  "52"
#define PCODE_CODE_LEFT_ARROW_KP_CTRL   "0;115"
#define PCODE_CODE_RIGHT_ARROW_KP       "0;77"
#define PCODE_CODE_RIGHT_ARROW_KP_SHIFT "54"
#define PCODE_CODE_RIGHT_ARROW_KP_CTRL  "0;116"
#define PCODE_CODE_END_KP               "0;79"
#define PCODE_CODE_END_KP_SHIFT         "49"
#define PCODE_CODE_END_KP_CTRL          "0;117"
#define PCODE_CODE_DOWN_ARROW_KP        "0;80"
#define PCODE_CODE_DOWN_ARROW_KP_SHIFT  "50"
#define PCODE_CODE_DOWN_ARROW_KP_CTRL   "0;145"
#define PCODE_CODE_PAGE_DOWN_KP         "0;81"
#define PCODE_CODE_PAGE_DOWN_KP_SHIFT   "51"
#define PCODE_CODE_PAGE_DOWN_KP_CTRL    "0;118"
#define PCODE_CODE_INSERT_KP            "0;82"
#define PCODE_CODE_INSERT_KP_SHIFT      "48"
#define PCODE_CODE_INSERT_KP_CTRL       "0;146"
#define PCODE_CODE_DELETE_KP            "0;83"
#define PCODE_CODE_DELETE_KP_SHIFT      "46"
#define PCODE_CODE_DELETE_KP_CTRL       "0;147"
#define PCODE_CODE_HOME                 "224;71"
#define PCODE_CODE_HOME_SHIFT           "224;71"
#define PCODE_CODE_HOME_CTRL            "224;119"
#define PCODE_CODE_HOME_ALT             "224;151"
#define PCODE_CODE_UP_ARROW             "224;72"
#define PCODE_CODE_UP_ARROW_SHIFT       "224;72"
#define PCODE_CODE_UP_ARROW_CTRL        "224;141"
#define PCODE_CODE_UP_ARROW_ALT         "224;152"
#define PCODE_CODE_PAGE_UP              "224;73"
#define PCODE_CODE_PAGE_UP_SHIFT        "224;73"
#define PCODE_CODE_PAGE_UP_CTRL         "224;132"
#define PCODE_CODE_PAGE_UP_ALT          "224;153"
#define PCODE_CODE_LEFT_ARROW           "224;75"
#define PCODE_CODE_LEFT_ARROW_SHIFT     "224;75"
#define PCODE_CODE_LEFT_ARROW_CTRL      "224;115"
#define PCODE_CODE_LEFT_ARROW_ALT       "224;155"
#define PCODE_CODE_RIGHT_ARROW          "224;77"
#define PCODE_CODE_RIGHT_ARROW_SHIFT    "224;77"
#define PCODE_CODE_RIGHT_ARROW_CTRL     "224;116"
#define PCODE_CODE_RIGHT_ARROW_ALT      "224;157"
#define PCODE_CODE_END                  "224;79"
#define PCODE_CODE_END_SHIFT            "224;79"
#define PCODE_CODE_END_CTRL             "224;117"
#define PCODE_CODE_END_ALT              "224;159"
#define PCODE_CODE_DOWN_ARROW           "224;80"
#define PCODE_CODE_DOWN_ARROW_SHIFT     "224;80"
#define PCODE_CODE_DOWN_ARROW_CTRL      "224;145"
#define PCODE_CODE_DOWN_ARROW_ALT       "224;154"
#define PCODE_CODE_PAGE_DOWN            "224;81"
#define PCODE_CODE_PAGE_DOWN_SHIFT      "224;81"
#define PCODE_CODE_PAGE_DOWN_CTRL       "224;118"
#define PCODE_CODE_PAGE_DOWN_ALT        "224;161"
#define PCODE_CODE_INSERT               "224;82"
#define PCODE_CODE_INSERT_SHIFT         "224;82"
#define PCODE_CODE_INSERT_CTRL          "224;146"
#define PCODE_CODE_INSERT_ALT           "224;162"
#define PCODE_CODE_DELETE               "224;83"
#define PCODE_CODE_DELETE_SHIFT         "224;83"
#define PCODE_CODE_DELETE_CTRL          "224;147"
#define PCODE_CODE_DELETE_ALT           "224;163"
#define PCODE_CODE_PRINT_SCREEN_CTRL    "0;114"
#define PCODE_CODE_PAUSE_BREAK_CTRL     "0;0"
#define PCODE_CODE_BACKSPACE            "8"
#define PCODE_CODE_BACKSPACE_SHIFT      "8"
#define PCODE_CODE_BACKSPACE_CTRL       "127"
/* #define PCODE_CODE_BACKSPACE_ALT        "0" */
#define PCODE_CODE_ENTER                "13"
#define PCODE_CODE_ENTER_CTRL           "10"
/* #define PCODE_CODE_ENTER_ALT            "0" */
#define PCODE_CODE_TAB                  "9"
#define PCODE_CODE_TAB_SHIFT            "0;15"
#define PCODE_CODE_TAB_CTRL             "0;148"
#define PCODE_CODE_TAB_ALT              "0;165"
/* #define PCODE_CODE_NULL                 "0;3" */
#define PCODE_CODE_A                    "97"
#define PCODE_CODE_A_SHIFT              "65"
#define PCODE_CODE_A_CTRL               "1"
#define PCODE_CODE_A_ALT                "0;30"
#define PCODE_CODE_B                    "98"
#define PCODE_CODE_B_SHIFT              "66"
#define PCODE_CODE_B_CTRL               "2"
#define PCODE_CODE_B_ALT                "0;48"
#define PCODE_CODE_C                    "99"
#define PCODE_CODE_C_SHIFT              "66"
#define PCODE_CODE_C_CTRL               "3"
#define PCODE_CODE_C_ALT                "0;46"
#define PCODE_CODE_D                    "100"
#define PCODE_CODE_D_SHIFT              "68"
#define PCODE_CODE_D_CTRL               "4"
#define PCODE_CODE_D_ALT                "0;32"
#define PCODE_CODE_E                    "101"
#define PCODE_CODE_E_SHIFT              "69"
#define PCODE_CODE_E_CTRL               "5"
#define PCODE_CODE_E_ALT                "0;18"
#define PCODE_CODE_F                    "102"
#define PCODE_CODE_F_SHIFT              "70"
#define PCODE_CODE_F_CTRL               "6"
#define PCODE_CODE_F_ALT                "0;33"
#define PCODE_CODE_G                    "103"
#define PCODE_CODE_G_SHIFT              "71"
#define PCODE_CODE_G_CTRL               "7"
#define PCODE_CODE_G_ALT                "0;34"
#define PCODE_CODE_H                    "104"
#define PCODE_CODE_H_SHIFT              "72"
#define PCODE_CODE_H_CTRL               "8"
#define PCODE_CODE_H_ALT                "0;35"
#define PCODE_CODE_I                    "105"
#define PCODE_CODE_I_SHIFT              "73"
#define PCODE_CODE_I_CTRL               "9"
#define PCODE_CODE_I_ALT                "0;23"
#define PCODE_CODE_J                    "106"
#define PCODE_CODE_J_SHIFT              "74"
#define PCODE_CODE_J_CTRL               "10"
#define PCODE_CODE_J_ALT                "0;36"
#define PCODE_CODE_K                    "107"
#define PCODE_CODE_K_SHIFT              "75"
#define PCODE_CODE_K_CTRL               "11"
#define PCODE_CODE_K_ALT                "0;37"
#define PCODE_CODE_L                    "108"
#define PCODE_CODE_L_SHIFT              "76"
#define PCODE_CODE_L_CTRL               "12"
#define PCODE_CODE_L_ALT                "0;38"
#define PCODE_CODE_M                    "109"
#define PCODE_CODE_M_SHIFT              "77"
#define PCODE_CODE_M_CTRL               "13"
#define PCODE_CODE_M_ALT                "0;50"
#define PCODE_CODE_N                    "110"
#define PCODE_CODE_N_SHIFT              "78"
#define PCODE_CODE_N_CTRL               "14"
#define PCODE_CODE_N_ALT                "0;49"
#define PCODE_CODE_O                    "111"
#define PCODE_CODE_O_SHIFT              "79"
#define PCODE_CODE_O_CTRL               "15"
#define PCODE_CODE_O_ALT                "0;24"
#define PCODE_CODE_P                    "112"
#define PCODE_CODE_P_SHIFT              "80"
#define PCODE_CODE_P_CTRL               "16"
#define PCODE_CODE_P_ALT                "0;25"
#define PCODE_CODE_Q                    "113"
#define PCODE_CODE_Q_SHIFT              "81"
#define PCODE_CODE_Q_CTRL               "17"
#define PCODE_CODE_Q_ALT                "0;16"
#define PCODE_CODE_R                    "114"
#define PCODE_CODE_R_SHIFT              "82"
#define PCODE_CODE_R_CTRL               "18"
#define PCODE_CODE_R_ALT                "0;19"
#define PCODE_CODE_S                    "115"
#define PCODE_CODE_S_SHIFT              "83"
#define PCODE_CODE_S_CTRL               "19"
#define PCODE_CODE_S_ALT                "0;31"
#define PCODE_CODE_T                    "116"
#define PCODE_CODE_T_SHIFT              "84"
#define PCODE_CODE_T_CTRL               "20"
#define PCODE_CODE_T_ALT                "0;20"
#define PCODE_CODE_U                    "117"
#define PCODE_CODE_U_SHIFT              "85"
#define PCODE_CODE_U_CTRL               "21"
#define PCODE_CODE_U_ALT                "0;22"
#define PCODE_CODE_V                    "118"
#define PCODE_CODE_V_SHIFT              "86"
#define PCODE_CODE_V_CTRL               "22"
#define PCODE_CODE_V_ALT                "0;47"
#define PCODE_CODE_W                    "119"
#define PCODE_CODE_W_SHIFT              "87"
#define PCODE_CODE_W_CTRL               "23"
#define PCODE_CODE_W_ALT                "0;17"
#define PCODE_CODE_X                    "120"
#define PCODE_CODE_X_SHIFT              "88"
#define PCODE_CODE_X_CTRL               "24"
#define PCODE_CODE_X_ALT                "0;45"
#define PCODE_CODE_Y                    "121"
#define PCODE_CODE_Y_SHIFT              "89"
#define PCODE_CODE_Y_CTRL               "25"
#define PCODE_CODE_Y_ALT                "0;21"
#define PCODE_CODE_Z                    "122"
#define PCODE_CODE_Z_SHIFT              "90"
#define PCODE_CODE_Z_CTRL               "26"
#define PCODE_CODE_Z_ALT                "0;44"
#define PCODE_CODE_1                    "49"
#define PCODE_CODE_1_SHIFT              "33"
#define PCODE_CODE_1_ALT                "0;120"
#define PCODE_CODE_2                    "50"
#define PCODE_CODE_2_SHIFT              "64"
/* #define PCODE_CODE_2_CTRL               "0" */
#define PCODE_CODE_2_ALT                "0;121"
#define PCODE_CODE_3                    "51"
#define PCODE_CODE_3_SHIFT              "35"
#define PCODE_CODE_3_ALT                "0;122"
#define PCODE_CODE_4                    "52"
#define PCODE_CODE_4_SHIFT              "36"
#define PCODE_CODE_4_ALT                "0;123"
#define PCODE_CODE_5                    "53"
#define PCODE_CODE_5_SHIFT              "37"
#define PCODE_CODE_5_ALT                "0;124"
#define PCODE_CODE_6                    "54"
#define PCODE_CODE_6_SHIFT              "94"
#define PCODE_CODE_6_CTRL               "30"
#define PCODE_CODE_6_ALT                "0;125"
#define PCODE_CODE_7                    "55"
#define PCODE_CODE_7_SHIFT              "38"
#define PCODE_CODE_7_ALT                "0;126"
#define PCODE_CODE_8                    "56"
#define PCODE_CODE_8_SHIFT              "42"
#define PCODE_CODE_8_ALT                "0;126"
#define PCODE_CODE_9                    "57"
#define PCODE_CODE_9_SHIFT              "40"
#define PCODE_CODE_9_ALT                "0;127"
#define PCODE_CODE_0                    "48"
#define PCODE_CODE_0_SHIFT              "41"
#define PCODE_CODE_0_ALT                "0;129"
#define PCODE_CODE_MINUS                "45"
#define PCODE_CODE_MINUS_SHIFT          "95"
#define PCODE_CODE_MINUS_CTRL           "31"
#define PCODE_CODE_MINUS_ALT            "0;130"
#define PCODE_CODE_EQUALS               "61"
#define PCODE_CODE_EQUALS_SHIFT         "43"
#define PCODE_CODE_EQUALS_ALT           "0;131"
/* #define PCODE_CODE_L_BRACK              "91" */
/* #define PCODE_CODE_L_BRACK_SHIFT        "123" */
/* #define PCODE_CODE_L_BRACK_CTRL         "27" */
/* #define PCODE_CODE_L_BRACK_ALT          "0;26" */
/* #define PCODE_CODE_R_BRACK              "93" */
/* #define PCODE_CODE_R_BRACK_SHIFT        "125" */
/* #define PCODE_CODE_R_BRACK_CTRL         "29" */
/* #define PCODE_CODE_R_BRACK_ALT          "0;27" */
#define PCODE_CODE_SPACE                "92"
#define PCODE_CODE_SPACE_SHIFT          "124"
#define PCODE_CODE_SPACE_CTRL           "28"
#define PCODE_CODE_SPACE_ALT            "0;43"
#define PCODE_CODE_SEMICOLON            "59"
#define PCODE_CODE_SEMICOLON_SHIFT      "58"
#define PCODE_CODE_SEMICOLON_ALT        "0;39"
/* #define PCODE_CODE_S_QUOTE              "39" */
/* #define PCODE_CODE_S_QUOTE_SHIFT        "34" */
/* #define PCODE_CODE_S_QUOTE_ALT          "0;40" */
#define PCODE_CODE_COMMA                "44"
#define PCODE_CODE_COMMA_SHIFT          "60"
#define PCODE_CODE_COMMA_ALT            "0;51"
#define PCODE_CODE_PERIOD               "46"
#define PCODE_CODE_PERIOD_SHIFT         "62"
#define PCODE_CODE_PERIOD_ALT           "0;52"
#define PCODE_CODE_SLASH                "47"
#define PCODE_CODE_SLASH_SHIFT          "63"
#define PCODE_CODE_SLASH_ALT            "0;53"
/* #define PCODE_CODE_BACKQUOTE            "96" */
/* #define PCODE_CODE_BACKQUOTE_SHIFT      "126" */
/* #define PCODE_CODE_BACKQUOTE_ALT        "0;41" */
#define PCODE_CODE_ENTER_KP             "13"
#define PCODE_CODE_ENTER_KP_CTRL        "10"
#define PCODE_CODE_ENTER_KP_ALT         "0;166"
#define PCODE_CODE_SLASH_KP             "47"
#define PCODE_CODE_SLASH_KP_SHIFT       "47"
#define PCODE_CODE_SLASH_KP_CTRL        "0;142"
#define PCODE_CODE_SLASH_KP_ALT         "0;74"
#define PCODE_CODE_MULT_KP              "42"
#define PCODE_CODE_MULT_KP_SHIFT        "0;144"
#define PCODE_CODE_MULT_KP_CTRL         "0;78"
#define PCODE_CODE_SUB_KP               "45"
#define PCODE_CODE_SUB_KP_SHIFT         "45"
#define PCODE_CODE_SUB_KP_CTRL          "0;149"
#define PCODE_CODE_SUB_KP_ALT           "0;164"
#define PCODE_CODE_ADD_KP               "43"
#define PCODE_CODE_ADD_KP_SHIFT         "43"
#define PCODE_CODE_ADD_KP_CTRL          "0;150"
#define PCODE_CODE_ADD_KP_ALT           "0;55"
#define PCODE_CODE_5_KP                 "0;76"
#define PCODE_CODE_5_KP_SHIFT           "53"
#define PCODE_CODE_5_KP_CTRL            "0;143"

/* need to keep this matched to enum ansi_pcodes */

static char *ansi_p_codes[] = {
    PCODE_CODE_F1,
    PCODE_CODE_F1_SHIFT,
    PCODE_CODE_F1_CTRL,
    PCODE_CODE_F1_ALT,
    PCODE_CODE_F2,
    PCODE_CODE_F2_SHIFT,
    PCODE_CODE_F2_CTRL,
    PCODE_CODE_F2_ALT,
    PCODE_CODE_F3,
    PCODE_CODE_F3_SHIFT,
    PCODE_CODE_F3_CTRL,
    PCODE_CODE_F3_ALT,
    PCODE_CODE_F4,
    PCODE_CODE_F4_SHIFT,
    PCODE_CODE_F4_CTRL,
    PCODE_CODE_F4_ALT,
    PCODE_CODE_F5,
    PCODE_CODE_F5_SHIFT,
    PCODE_CODE_F5_CTRL,
    PCODE_CODE_F5_ALT,
    PCODE_CODE_F6,
    PCODE_CODE_F6_SHIFT,
    PCODE_CODE_F6_CTRL,
    PCODE_CODE_F6_ALT,
    PCODE_CODE_F7,
    PCODE_CODE_F7_SHIFT,
    PCODE_CODE_F7_CTRL,
    PCODE_CODE_F7_ALT,
    PCODE_CODE_F8,
    PCODE_CODE_F8_SHIFT,
    PCODE_CODE_F8_CTRL,
    PCODE_CODE_F8_ALT,
    PCODE_CODE_F9,
    PCODE_CODE_F9_SHIFT,
    PCODE_CODE_F9_CTRL,
    PCODE_CODE_F9_ALT,
    PCODE_CODE_F10,
    PCODE_CODE_F10_SHIFT,
    PCODE_CODE_F10_CTRL,
    PCODE_CODE_F10_ALT,
    PCODE_CODE_F11,
    PCODE_CODE_F11_SHIFT,
    PCODE_CODE_F11_CTRL,
    PCODE_CODE_F11_ALT,
    PCODE_CODE_F12,
    PCODE_CODE_F12_SHIFT,
    PCODE_CODE_F12_CTRL,
    PCODE_CODE_F12_ALT,
    PCODE_CODE_HOME_KP,
    PCODE_CODE_HOME_KP_SHIFT,
    PCODE_CODE_HOME_KP_CTRL,
    PCODE_CODE_UP_ARROW_KP,
    PCODE_CODE_UP_ARROW_KP_SHIFT,
    PCODE_CODE_UP_ARROW_KP_CTRL,
    PCODE_CODE_PAGE_UP_KP,
    PCODE_CODE_PAGE_UP_KP_SHIFT,
    PCODE_CODE_PAGE_UP_KP_CTRL,
    PCODE_CODE_LEFT_ARROW_KP,
    PCODE_CODE_LEFT_ARROW_KP_SHIFT,
    PCODE_CODE_LEFT_ARROW_KP_CTRL,
    PCODE_CODE_RIGHT_ARROW_KP,
    PCODE_CODE_RIGHT_ARROW_KP_SHIFT,
    PCODE_CODE_RIGHT_ARROW_KP_CTRL,
    PCODE_CODE_END_KP,
    PCODE_CODE_END_KP_SHIFT,
    PCODE_CODE_END_KP_CTRL,
    PCODE_CODE_DOWN_ARROW_KP,
    PCODE_CODE_DOWN_ARROW_KP_SHIFT,
    PCODE_CODE_DOWN_ARROW_KP_CTRL,
    PCODE_CODE_PAGE_DOWN_KP,
    PCODE_CODE_PAGE_DOWN_KP_SHIFT,
    PCODE_CODE_PAGE_DOWN_KP_CTRL,
    PCODE_CODE_INSERT_KP,
    PCODE_CODE_INSERT_KP_SHIFT,
    PCODE_CODE_INSERT_KP_CTRL,
    PCODE_CODE_DELETE_KP,
    PCODE_CODE_DELETE_KP_SHIFT,
    PCODE_CODE_DELETE_KP_CTRL,
    PCODE_CODE_HOME,
    PCODE_CODE_HOME_SHIFT,
    PCODE_CODE_HOME_CTRL,
    PCODE_CODE_HOME_ALT,
    PCODE_CODE_UP_ARROW,
    PCODE_CODE_UP_ARROW_SHIFT,
    PCODE_CODE_UP_ARROW_CTRL,
    PCODE_CODE_UP_ARROW_ALT,
    PCODE_CODE_PAGE_UP,
    PCODE_CODE_PAGE_UP_SHIFT,
    PCODE_CODE_PAGE_UP_CTRL,
    PCODE_CODE_PAGE_UP_ALT,
    PCODE_CODE_LEFT_ARROW,
    PCODE_CODE_LEFT_ARROW_SHIFT,
    PCODE_CODE_LEFT_ARROW_CTRL,
    PCODE_CODE_LEFT_ARROW_ALT,
    PCODE_CODE_RIGHT_ARROW,
    PCODE_CODE_RIGHT_ARROW_SHIFT,
    PCODE_CODE_RIGHT_ARROW_CTRL,
    PCODE_CODE_RIGHT_ARROW_ALT,
    PCODE_CODE_END,
    PCODE_CODE_END_SHIFT,
    PCODE_CODE_END_CTRL,
    PCODE_CODE_END_ALT,
    PCODE_CODE_DOWN_ARROW,
    PCODE_CODE_DOWN_ARROW_SHIFT,
    PCODE_CODE_DOWN_ARROW_CTRL,
    PCODE_CODE_DOWN_ARROW_ALT,
    PCODE_CODE_PAGE_DOWN,
    PCODE_CODE_PAGE_DOWN_SHIFT,
    PCODE_CODE_PAGE_DOWN_CTRL,
    PCODE_CODE_PAGE_DOWN_ALT,
    PCODE_CODE_INSERT,
    PCODE_CODE_INSERT_SHIFT,
    PCODE_CODE_INSERT_CTRL,
    PCODE_CODE_INSERT_ALT,
    PCODE_CODE_DELETE,
    PCODE_CODE_DELETE_SHIFT,
    PCODE_CODE_DELETE_CTRL,
    PCODE_CODE_DELETE_ALT,
    PCODE_CODE_PRINT_SCREEN_CTRL,
    PCODE_CODE_PAUSE_BREAK_CTRL,
    PCODE_CODE_BACKSPACE,
    PCODE_CODE_BACKSPACE_SHIFT,
    PCODE_CODE_BACKSPACE_CTRL,
    /* PCODE_CODE_BACKSPACE_ALT, */
    PCODE_CODE_ENTER,
    PCODE_CODE_ENTER_CTRL,
    /* PCODE_CODE_ENTER_ALT, */
    PCODE_CODE_TAB,
    PCODE_CODE_TAB_SHIFT,
    PCODE_CODE_TAB_CTRL,
    PCODE_CODE_TAB_ALT,
    /* PCODE_CODE_NULL, */
    PCODE_CODE_A,
    PCODE_CODE_A_SHIFT,
    PCODE_CODE_A_CTRL,
    PCODE_CODE_A_ALT,
    PCODE_CODE_B,
    PCODE_CODE_B_SHIFT,
    PCODE_CODE_B_CTRL,
    PCODE_CODE_B_ALT,
    PCODE_CODE_C,
    PCODE_CODE_C_SHIFT,
    PCODE_CODE_C_CTRL,
    PCODE_CODE_C_ALT,
    PCODE_CODE_D,
    PCODE_CODE_D_SHIFT,
    PCODE_CODE_D_CTRL,
    PCODE_CODE_D_ALT,
    PCODE_CODE_E,
    PCODE_CODE_E_SHIFT,
    PCODE_CODE_E_CTRL,
    PCODE_CODE_E_ALT,
    PCODE_CODE_F,
    PCODE_CODE_F_SHIFT,
    PCODE_CODE_F_CTRL,
    PCODE_CODE_F_ALT,
    PCODE_CODE_G,
    PCODE_CODE_G_SHIFT,
    PCODE_CODE_G_CTRL,
    PCODE_CODE_G_ALT,
    PCODE_CODE_H,
    PCODE_CODE_H_SHIFT,
    PCODE_CODE_H_CTRL,
    PCODE_CODE_H_ALT,
    PCODE_CODE_I,
    PCODE_CODE_I_SHIFT,
    PCODE_CODE_I_CTRL,
    PCODE_CODE_I_ALT,
    PCODE_CODE_J,
    PCODE_CODE_J_SHIFT,
    PCODE_CODE_J_CTRL,
    PCODE_CODE_J_ALT,
    PCODE_CODE_K,
    PCODE_CODE_K_SHIFT,
    PCODE_CODE_K_CTRL,
    PCODE_CODE_K_ALT,
    PCODE_CODE_L,
    PCODE_CODE_L_SHIFT,
    PCODE_CODE_L_CTRL,
    PCODE_CODE_L_ALT,
    PCODE_CODE_M,
    PCODE_CODE_M_SHIFT,
    PCODE_CODE_M_CTRL,
    PCODE_CODE_M_ALT,
    PCODE_CODE_N,
    PCODE_CODE_N_SHIFT,
    PCODE_CODE_N_CTRL,
    PCODE_CODE_N_ALT,
    PCODE_CODE_O,
    PCODE_CODE_O_SHIFT,
    PCODE_CODE_O_CTRL,
    PCODE_CODE_O_ALT,
    PCODE_CODE_P,
    PCODE_CODE_P_SHIFT,
    PCODE_CODE_P_CTRL,
    PCODE_CODE_P_ALT,
    PCODE_CODE_Q,
    PCODE_CODE_Q_SHIFT,
    PCODE_CODE_Q_CTRL,
    PCODE_CODE_Q_ALT,
    PCODE_CODE_R,
    PCODE_CODE_R_SHIFT,
    PCODE_CODE_R_CTRL,
    PCODE_CODE_R_ALT,
    PCODE_CODE_S,
    PCODE_CODE_S_SHIFT,
    PCODE_CODE_S_CTRL,
    PCODE_CODE_S_ALT,
    PCODE_CODE_T,
    PCODE_CODE_T_SHIFT,
    PCODE_CODE_T_CTRL,
    PCODE_CODE_T_ALT,
    PCODE_CODE_U,
    PCODE_CODE_U_SHIFT,
    PCODE_CODE_U_CTRL,
    PCODE_CODE_U_ALT,
    PCODE_CODE_V,
    PCODE_CODE_V_SHIFT,
    PCODE_CODE_V_CTRL,
    PCODE_CODE_V_ALT,
    PCODE_CODE_W,
    PCODE_CODE_W_SHIFT,
    PCODE_CODE_W_CTRL,
    PCODE_CODE_W_ALT,
    PCODE_CODE_X,
    PCODE_CODE_X_SHIFT,
    PCODE_CODE_X_CTRL,
    PCODE_CODE_X_ALT,
    PCODE_CODE_Y,
    PCODE_CODE_Y_SHIFT,
    PCODE_CODE_Y_CTRL,
    PCODE_CODE_Y_ALT,
    PCODE_CODE_Z,
    PCODE_CODE_Z_SHIFT,
    PCODE_CODE_Z_CTRL,
    PCODE_CODE_Z_ALT,
    PCODE_CODE_1,
    PCODE_CODE_1_SHIFT,
    PCODE_CODE_1_ALT,
    PCODE_CODE_2,
    PCODE_CODE_2_SHIFT,
    /* PCODE_CODE_2_CTRL, */
    PCODE_CODE_2_ALT,
    PCODE_CODE_3,
    PCODE_CODE_3_SHIFT,
    PCODE_CODE_3_ALT,
    PCODE_CODE_4,
    PCODE_CODE_4_SHIFT,
    PCODE_CODE_4_ALT,
    PCODE_CODE_5,
    PCODE_CODE_5_SHIFT,
    PCODE_CODE_5_ALT,
    PCODE_CODE_6,
    PCODE_CODE_6_SHIFT,
    PCODE_CODE_6_CTRL,
    PCODE_CODE_6_ALT,
    PCODE_CODE_7,
    PCODE_CODE_7_SHIFT,
    PCODE_CODE_7_ALT,
    PCODE_CODE_8,
    PCODE_CODE_8_SHIFT,
    PCODE_CODE_8_ALT,
    PCODE_CODE_9,
    PCODE_CODE_9_SHIFT,
    PCODE_CODE_9_ALT,
    PCODE_CODE_0,
    PCODE_CODE_0_SHIFT,
    PCODE_CODE_0_ALT,
    PCODE_CODE_MINUS,
    PCODE_CODE_MINUS_SHIFT,
    PCODE_CODE_MINUS_CTRL,
    PCODE_CODE_MINUS_ALT,
    PCODE_CODE_EQUALS,
    PCODE_CODE_EQUALS_SHIFT,
    PCODE_CODE_EQUALS_ALT,
    /* PCODE_CODE_L_BRACK, */
    /* PCODE_CODE_L_BRACK_SHIFT, */
    /* PCODE_CODE_L_BRACK_CTRL, */
    /* PCODE_CODE_L_BRACK_ALT, */
    /* PCODE_CODE_R_BRACK, */
    /* PCODE_CODE_R_BRACK_SHIFT, */
    /* PCODE_CODE_R_BRACK_CTRL, */
    /* PCODE_CODE_R_BRACK_ALT, */
    PCODE_CODE_SPACE,
    PCODE_CODE_SPACE_SHIFT,
    PCODE_CODE_SPACE_CTRL,
    PCODE_CODE_SPACE_ALT,
    PCODE_CODE_SEMICOLON,
    PCODE_CODE_SEMICOLON_SHIFT,
    PCODE_CODE_SEMICOLON_ALT,
    /* PCODE_CODE_S_QUOTE, */
    /* PCODE_CODE_S_QUOTE_SHIFT, */
    /* PCODE_CODE_S_QUOTE_ALT, */
    PCODE_CODE_COMMA,
    PCODE_CODE_COMMA_SHIFT,
    PCODE_CODE_COMMA_ALT,
    PCODE_CODE_PERIOD,
    PCODE_CODE_PERIOD_SHIFT,
    PCODE_CODE_PERIOD_ALT,
    PCODE_CODE_SLASH,
    PCODE_CODE_SLASH_SHIFT,
    PCODE_CODE_SLASH_ALT,
    /* PCODE_CODE_BACKQUOTE, */
    /* PCODE_CODE_BACKQUOTE_SHIFT, */
    /* PCODE_CODE_BACKQUOTE_ALT, */
    PCODE_CODE_ENTER_KP,
    PCODE_CODE_ENTER_KP_CTRL,
    PCODE_CODE_ENTER_KP_ALT,
    PCODE_CODE_SLASH_KP,
    PCODE_CODE_SLASH_KP_SHIFT,
    PCODE_CODE_SLASH_KP_CTRL,
    PCODE_CODE_SLASH_KP_ALT,
    PCODE_CODE_MULT_KP,
    PCODE_CODE_MULT_KP_SHIFT,
    PCODE_CODE_MULT_KP_CTRL,
    PCODE_CODE_SUB_KP,
    PCODE_CODE_SUB_KP_SHIFT,
    PCODE_CODE_SUB_KP_CTRL,
    PCODE_CODE_SUB_KP_ALT,
    PCODE_CODE_ADD_KP,
    PCODE_CODE_ADD_KP_SHIFT,
    PCODE_CODE_ADD_KP_CTRL,
    PCODE_CODE_ADD_KP_ALT,
    PCODE_CODE_5_KP,
    PCODE_CODE_5_KP_SHIFT,
    PCODE_CODE_5_KP_CTRL,
};

char *
telnetp_get_p_code(int type)
{
    return ansi_p_codes[type];
}
