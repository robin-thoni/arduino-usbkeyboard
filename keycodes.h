//
// Created by robin on 1/9/16.
//

#ifndef USBKEYBOARD_KEYCODES_H
#define USBKEYBOARD_KEYCODES_H


/* Keyboard usage values, see usb.org's HID-usage-tables document, chapter
 * 10 Keyboard/Keypad Page for more codes.
 */
#define MOD_CONTROL_LEFT    (1<<0)
#define MOD_SHIFT_LEFT      (1<<1)
#define MOD_ALT_LEFT        (1<<2)
#define MOD_GUI_LEFT        (1<<3)
#define MOD_CONTROL_RIGHT   (1<<4)
#define MOD_SHIFT_RIGHT     (1<<5)
#define MOD_ALT_RIGHT       (1<<6)
#define MOD_GUI_RIGHT       (1<<7)

#define KEY_A       4
#define KEY_B       5
#define KEY_C       6
#define KEY_D       7
#define KEY_E       8
#define KEY_F       9
#define KEY_G       10
#define KEY_H       11
#define KEY_I       12
#define KEY_J       13
#define KEY_K       14
#define KEY_L       15
#define KEY_M       16
#define KEY_N       17
#define KEY_O       18
#define KEY_P       19
#define KEY_Q       20
#define KEY_R       21
#define KEY_S       22
#define KEY_T       23
#define KEY_U       24
#define KEY_V       25
#define KEY_W       26
#define KEY_X       27
#define KEY_Y       28
#define KEY_Z       29
#define KEY_1       30
#define KEY_2       31
#define KEY_3       32
#define KEY_4       33
#define KEY_5       34
#define KEY_6       35
#define KEY_7       36
#define KEY_8       37
#define KEY_9       38
#define KEY_0       39

#define KEY_ENTER   40
#define KEY_ESCAPE  41
#define KEY_BSPACE  42
#define KEY_TAB     43
#define KEY_SPACE   44


#define KEY_HYPHEN    45
#define KEY_EQUAL     46
#define KEY_LBRACKET  47
#define KEY_RBRACKET  48
#define KEY_BSLASH    49
#define KEY_HASHTAG   50
#define KEY_SEMICOLON 51
#define KEY_QUOTE    52
#define KEY_TILDE     53
#define KEY_COMMA     54
#define KEY_DOT       55
#define KEY_SLASH     56
#define KEY_CAPSLOCK  57

#define KEY_F1      58
#define KEY_F2      59
#define KEY_F3      60
#define KEY_F4      61
#define KEY_F5      62
#define KEY_F6      63
#define KEY_F7      64
#define KEY_F8      65
#define KEY_F9      66
#define KEY_F10     67
#define KEY_F11     68
#define KEY_F12     69

#define KEY_PRINTSCREEN 70
#define KEY_SCROLLLOCK  71
#define KEY_PAUSE       72
#define KEY_INSERT      73
#define KEY_HOME        74
#define KEY_PAGEUP      75
#define KEY_DELETE      76
#define KEY_END         77
#define KEY_PAGEDOWN    78

#define KEY_ARROW_RIGHT 79
#define KEY_ARROW_LEFT  80
#define KEY_ARROW_DOWN  81
#define KEY_ARROW_UP    82


#define KEY_NUMLOCK     83
#define KEYP_SLASH      84
#define KEYP_STAR       85
#define KEYP_MINUS      86
#define KEYP_PLUS       87
#define KEYP_ENTER      88


#define KEYP_NUS_BSLASH 100

#endif //USBKEYBOARD_KEYCODES_H
