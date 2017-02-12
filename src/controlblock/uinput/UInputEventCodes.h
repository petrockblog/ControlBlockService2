/**
 * (c) Copyright 2017  Florian Müller (contact@petrockblock.com)
 * https://github.com/petrockblog/ControlBlock2
 *
 * Permission to use, copy, modify and distribute the program in both binary and
 * source form, for non-commercial purposes, is hereby granted without fee,
 * providing that this license information and copyright notice appear with
 * all copies and any derived work.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event shall the authors be held liable for any damages
 * arising from the use of this software.
 *
 * This program is freeware for PERSONAL USE only. Commercial users must
 * seek permission of the copyright holders first. Commercial use includes
 * charging money for the program or software derived from the program.
 *
 * The copyright holders request that bug fixes and improvements to the code
 * should be forwarded to them so everyone can benefit from the modifications
 * in future versions.
 */

#ifndef CONTROLBLOCKSERVICE2_UINPUTEVENTCODES_H
#define CONTROLBLOCKSERVICE2_UINPUTEVENTCODES_H

/**
 * All event codes are taken from input-event-codes.h
 */

#include <stdint.h>

static const uint16_t INPUT_PROP_POINTER = 0x00;    /* needs a pointer */
static const uint16_t INPUT_PROP_DIRECT = 0x01;    /* direct input devices */
static const uint16_t INPUT_PROP_BUTTONPAD = 0x02;    /* has button(s) under pad */
static const uint16_t INPUT_PROP_SEMI_MT = 0x03;    /* touch rectangle only */
static const uint16_t INPUT_PROP_TOPBUTTONPAD = 0x04;    /* softbuttons at top of pad */
static const uint16_t INPUT_PROP_POINTING_STICK = 0x05;    /* is a pointing stick */
static const uint16_t INPUT_PROP_ACCELEROMETER = 0x06;    /* has accelerometer */

static const uint16_t INPUT_PROP_MAX = 0x1f;
static const uint16_t INPUT_PROP_CNT = (INPUT_PROP_MAX+1);

/*
 * Event types
 */

static const uint16_t EV_SYN = 0x00;
static const uint16_t EV_KEY = 0x01;
static const uint16_t EV_REL = 0x02;
static const uint16_t EV_ABS = 0x03;
static const uint16_t EV_MSC = 0x04;
static const uint16_t EV_SW = 0x05;
static const uint16_t EV_LED = 0x11;
static const uint16_t EV_SND = 0x12;
static const uint16_t EV_REP = 0x14;
static const uint16_t EV_FF = 0x15;
static const uint16_t EV_PWR = 0x16;
static const uint16_t EV_FF_STATUS = 0x17;
static const uint16_t EV_MAX = 0x1f;
static const uint16_t EV_CNT = (EV_MAX+1);

/*
 * Synchronization events.
 */

static const uint16_t SYN_REPORT = 0;
static const uint16_t SYN_CONFIG = 1;
static const uint16_t SYN_MT_REPORT = 2;
static const uint16_t SYN_DROPPED = 3;
static const uint16_t SYN_MAX = 0xf;
static const uint16_t SYN_CNT = (SYN_MAX+1);

/*
 * Keys and buttons
 *
 * Most of the keys/buttons are modeled after USB HUT 1.12
 * (see http://www.usb.org/developers/hidpage).
 * Abbreviations in the comments:
 * AC - Application Control
 * AL - Application Launch Button
 * SC - System Control
 */

static const uint16_t KEY_RESERVED = 0;
static const uint16_t KEY_ESC = 1;
static const uint16_t KEY_1 = 2;
static const uint16_t KEY_2 = 3;
static const uint16_t KEY_3 = 4;
static const uint16_t KEY_4 = 5;
static const uint16_t KEY_5 = 6;
static const uint16_t KEY_6 = 7;
static const uint16_t KEY_7 = 8;
static const uint16_t KEY_8 = 9;
static const uint16_t KEY_9 = 10;
static const uint16_t KEY_0 = 11;
static const uint16_t KEY_MINUS = 12;
static const uint16_t KEY_EQUAL = 13;
static const uint16_t KEY_BACKSPACE = 14;
static const uint16_t KEY_TAB = 15;
static const uint16_t KEY_Q = 16;
static const uint16_t KEY_W = 17;
static const uint16_t KEY_E = 18;
static const uint16_t KEY_R = 19;
static const uint16_t KEY_T = 20;
static const uint16_t KEY_Y = 21;
static const uint16_t KEY_U = 22;
static const uint16_t KEY_I = 23;
static const uint16_t KEY_O = 24;
static const uint16_t KEY_P = 25;
static const uint16_t KEY_LEFTBRACE = 26;
static const uint16_t KEY_RIGHTBRACE = 27;
static const uint16_t KEY_ENTER = 28;
static const uint16_t KEY_LEFTCTRL = 29;
static const uint16_t KEY_A = 30;
static const uint16_t KEY_S = 31;
static const uint16_t KEY_D = 32;
static const uint16_t KEY_F = 33;
static const uint16_t KEY_G = 34;
static const uint16_t KEY_H = 35;
static const uint16_t KEY_J = 36;
static const uint16_t KEY_K = 37;
static const uint16_t KEY_L = 38;
static const uint16_t KEY_SEMICOLON = 39;
static const uint16_t KEY_APOSTROPHE = 40;
static const uint16_t KEY_GRAVE = 41;
static const uint16_t KEY_LEFTSHIFT = 42;
static const uint16_t KEY_BACKSLASH = 43;
static const uint16_t KEY_Z = 44;
static const uint16_t KEY_X = 45;
static const uint16_t KEY_C = 46;
static const uint16_t KEY_V = 47;
static const uint16_t KEY_B = 48;
static const uint16_t KEY_N = 49;
static const uint16_t KEY_M = 50;
static const uint16_t KEY_COMMA = 51;
static const uint16_t KEY_DOT = 52;
static const uint16_t KEY_SLASH = 53;
static const uint16_t KEY_RIGHTSHIFT = 54;
static const uint16_t KEY_KPASTERISK = 55;
static const uint16_t KEY_LEFTALT = 56;
static const uint16_t KEY_SPACE = 57;
static const uint16_t KEY_CAPSLOCK = 58;
static const uint16_t KEY_F1 = 59;
static const uint16_t KEY_F2 = 60;
static const uint16_t KEY_F3 = 61;
static const uint16_t KEY_F4 = 62;
static const uint16_t KEY_F5 = 63;
static const uint16_t KEY_F6 = 64;
static const uint16_t KEY_F7 = 65;
static const uint16_t KEY_F8 = 66;
static const uint16_t KEY_F9 = 67;
static const uint16_t KEY_F10 = 68;
static const uint16_t KEY_NUMLOCK = 69;
static const uint16_t KEY_SCROLLLOCK = 70;
static const uint16_t KEY_KP7 = 71;
static const uint16_t KEY_KP8 = 72;
static const uint16_t KEY_KP9 = 73;
static const uint16_t KEY_KPMINUS = 74;
static const uint16_t KEY_KP4 = 75;
static const uint16_t KEY_KP5 = 76;
static const uint16_t KEY_KP6 = 77;
static const uint16_t KEY_KPPLUS = 78;
static const uint16_t KEY_KP1 = 79;
static const uint16_t KEY_KP2 = 80;
static const uint16_t KEY_KP3 = 81;
static const uint16_t KEY_KP0 = 82;
static const uint16_t KEY_KPDOT = 83;

static const uint16_t KEY_ZENKAKUHANKAKU = 85;
static const uint16_t KEY_102ND = 86;
static const uint16_t KEY_F11 = 87;
static const uint16_t KEY_F12 = 88;
static const uint16_t KEY_RO = 89;
static const uint16_t KEY_KATAKANA = 90;
static const uint16_t KEY_HIRAGANA = 91;
static const uint16_t KEY_HENKAN = 92;
static const uint16_t KEY_KATAKANAHIRAGANA = 93;
static const uint16_t KEY_MUHENKAN = 94;
static const uint16_t KEY_KPJPCOMMA = 95;
static const uint16_t KEY_KPENTER = 96;
static const uint16_t KEY_RIGHTCTRL = 97;
static const uint16_t KEY_KPSLASH = 98;
static const uint16_t KEY_SYSRQ = 99;
static const uint16_t KEY_RIGHTALT = 100;
static const uint16_t KEY_LINEFEED = 101;
static const uint16_t KEY_HOME = 102;
static const uint16_t KEY_UP = 103;
static const uint16_t KEY_PAGEUP = 104;
static const uint16_t KEY_LEFT = 105;
static const uint16_t KEY_RIGHT = 106;
static const uint16_t KEY_END = 107;
static const uint16_t KEY_DOWN = 108;
static const uint16_t KEY_PAGEDOWN = 109;
static const uint16_t KEY_INSERT = 110;
static const uint16_t KEY_DELETE = 111;
static const uint16_t KEY_MACRO = 112;
static const uint16_t KEY_MUTE = 113;
static const uint16_t KEY_VOLUMEDOWN = 114;
static const uint16_t KEY_VOLUMEUP = 115;
static const uint16_t KEY_POWER = 116;    /* SC System Power Down */
static const uint16_t KEY_KPEQUAL = 117;
static const uint16_t KEY_KPPLUSMINUS = 118;
static const uint16_t KEY_PAUSE = 119;
static const uint16_t KEY_SCALE = 120;    /* AL Compiz Scale (Expose) */

static const uint16_t KEY_KPCOMMA = 121;
static const uint16_t KEY_HANGEUL = 122;
static const uint16_t KEY_HANGUEL = KEY_HANGEUL;
static const uint16_t KEY_HANJA = 123;
static const uint16_t KEY_YEN = 124;
static const uint16_t KEY_LEFTMETA = 125;
static const uint16_t KEY_RIGHTMETA = 126;
static const uint16_t KEY_COMPOSE = 127;

static const uint16_t KEY_STOP = 128;    /* AC Stop */
static const uint16_t KEY_AGAIN = 129;
static const uint16_t KEY_PROPS = 130;    /* AC Properties */
static const uint16_t KEY_UNDO = 131;    /* AC Undo */
static const uint16_t KEY_FRONT = 132;
static const uint16_t KEY_COPY = 133;    /* AC Copy */
static const uint16_t KEY_OPEN = 134;    /* AC Open */
static const uint16_t KEY_PASTE = 135;    /* AC Paste */
static const uint16_t KEY_FIND = 136;    /* AC Search */
static const uint16_t KEY_CUT = 137;    /* AC Cut */
static const uint16_t KEY_HELP = 138;    /* AL Integrated Help Center */
static const uint16_t KEY_MENU = 139;    /* Menu (show menu) */
static const uint16_t KEY_CALC = 140;    /* AL Calculator */
static const uint16_t KEY_SETUP = 141;
static const uint16_t KEY_SLEEP = 142;    /* SC System Sleep */
static const uint16_t KEY_WAKEUP = 143;    /* System Wake Up */
static const uint16_t KEY_FILE = 144;    /* AL Local Machine Browser */
static const uint16_t KEY_SENDFILE = 145;
static const uint16_t KEY_DELETEFILE = 146;
static const uint16_t KEY_XFER = 147;
static const uint16_t KEY_PROG1 = 148;
static const uint16_t KEY_PROG2 = 149;
static const uint16_t KEY_WWW = 150;    /* AL Internet Browser */
static const uint16_t KEY_MSDOS = 151;
static const uint16_t KEY_COFFEE = 152;    /* AL Terminal Lock/Screensaver */
static const uint16_t KEY_SCREENLOCK = KEY_COFFEE;
static const uint16_t KEY_ROTATE_DISPLAY = 153;    /* Display orientation for e.g. tablets */
static const uint16_t KEY_DIRECTION = KEY_ROTATE_DISPLAY;
static const uint16_t KEY_CYCLEWINDOWS = 154;
static const uint16_t KEY_MAIL = 155;
static const uint16_t KEY_BOOKMARKS = 156;    /* AC Bookmarks */
static const uint16_t KEY_COMPUTER = 157;
static const uint16_t KEY_BACK = 158;    /* AC Back */
static const uint16_t KEY_FORWARD = 159;    /* AC Forward */
static const uint16_t KEY_CLOSECD = 160;
static const uint16_t KEY_EJECTCD = 161;
static const uint16_t KEY_EJECTCLOSECD = 162;
static const uint16_t KEY_NEXTSONG = 163;
static const uint16_t KEY_PLAYPAUSE = 164;
static const uint16_t KEY_PREVIOUSSONG = 165;
static const uint16_t KEY_STOPCD = 166;
static const uint16_t KEY_RECORD = 167;
static const uint16_t KEY_REWIND = 168;
static const uint16_t KEY_PHONE = 169;    /* Media Select Telephone */
static const uint16_t KEY_ISO = 170;
static const uint16_t KEY_CONFIG = 171;    /* AL Consumer Control Configuration */
static const uint16_t KEY_HOMEPAGE = 172;    /* AC Home */
static const uint16_t KEY_REFRESH = 173;    /* AC Refresh */
static const uint16_t KEY_EXIT = 174;    /* AC Exit */
static const uint16_t KEY_MOVE = 175;
static const uint16_t KEY_EDIT = 176;
static const uint16_t KEY_SCROLLUP = 177;
static const uint16_t KEY_SCROLLDOWN = 178;
static const uint16_t KEY_KPLEFTPAREN = 179;
static const uint16_t KEY_KPRIGHTPAREN = 180;
static const uint16_t KEY_NEW = 181;    /* AC New */
static const uint16_t KEY_REDO = 182;    /* AC Redo/Repeat */

static const uint16_t KEY_F13 = 183;
static const uint16_t KEY_F14 = 184;
static const uint16_t KEY_F15 = 185;
static const uint16_t KEY_F16 = 186;
static const uint16_t KEY_F17 = 187;
static const uint16_t KEY_F18 = 188;
static const uint16_t KEY_F19 = 189;
static const uint16_t KEY_F20 = 190;
static const uint16_t KEY_F21 = 191;
static const uint16_t KEY_F22 = 192;
static const uint16_t KEY_F23 = 193;
static const uint16_t KEY_F24 = 194;

static const uint16_t KEY_PLAYCD = 200;
static const uint16_t KEY_PAUSECD = 201;
static const uint16_t KEY_PROG3 = 202;
static const uint16_t KEY_PROG4 = 203;
static const uint16_t KEY_DASHBOARD = 204;    /* AL Dashboard */
static const uint16_t KEY_SUSPEND = 205;
static const uint16_t KEY_CLOSE = 206;    /* AC Close */
static const uint16_t KEY_PLAY = 207;
static const uint16_t KEY_FASTFORWARD = 208;
static const uint16_t KEY_BASSBOOST = 209;
static const uint16_t KEY_PRINT = 210;    /* AC Print */
static const uint16_t KEY_HP = 211;
static const uint16_t KEY_CAMERA = 212;
static const uint16_t KEY_SOUND = 213;
static const uint16_t KEY_QUESTION = 214;
static const uint16_t KEY_EMAIL = 215;
static const uint16_t KEY_CHAT = 216;
static const uint16_t KEY_SEARCH = 217;
static const uint16_t KEY_CONNECT = 218;
static const uint16_t KEY_FINANCE = 219;    /* AL Checkbook/Finance */
static const uint16_t KEY_SPORT = 220;
static const uint16_t KEY_SHOP = 221;
static const uint16_t KEY_ALTERASE = 222;
static const uint16_t KEY_CANCEL = 223;    /* AC Cancel */
static const uint16_t KEY_BRIGHTNESSDOWN = 224;
static const uint16_t KEY_BRIGHTNESSUP = 225;
static const uint16_t KEY_MEDIA = 226;

static const uint16_t KEY_SWITCHVIDEOMODE = 227;    /* Cycle between available video
					   outputs (Monitor/LCD/TV-out/etc) */
static const uint16_t KEY_KBDILLUMTOGGLE = 228;
static const uint16_t KEY_KBDILLUMDOWN = 229;
static const uint16_t KEY_KBDILLUMUP = 230;

static const uint16_t KEY_SEND = 231;    /* AC Send */
static const uint16_t KEY_REPLY = 232;    /* AC Reply */
static const uint16_t KEY_FORWARDMAIL = 233;    /* AC Forward Msg */
static const uint16_t KEY_SAVE = 234;    /* AC Save */
static const uint16_t KEY_DOCUMENTS = 235;

static const uint16_t KEY_BATTERY = 236;

static const uint16_t KEY_BLUETOOTH = 237;
static const uint16_t KEY_WLAN = 238;
static const uint16_t KEY_UWB = 239;

static const uint16_t KEY_UNKNOWN = 240;

static const uint16_t KEY_VIDEO_NEXT = 241;    /* drive next video source */
static const uint16_t KEY_VIDEO_PREV = 242;    /* drive previous video source */
static const uint16_t KEY_BRIGHTNESS_CYCLE = 243;    /* brightness up, after max is min */
static const uint16_t KEY_BRIGHTNESS_AUTO = 244;    /* Set Auto Brightness: manual
					  brightness control is off,
					  rely on ambient */
static const uint16_t KEY_BRIGHTNESS_ZERO = KEY_BRIGHTNESS_AUTO;
static const uint16_t KEY_DISPLAY_OFF = 245;    /* display device to off state */

static const uint16_t KEY_WWAN = 246;    /* Wireless WAN (LTE, UMTS, GSM, etc.) */
static const uint16_t KEY_WIMAX = KEY_WWAN;
static const uint16_t KEY_RFKILL = 247;    /* Key that controls all radios */

static const uint16_t KEY_MICMUTE = 248;    /* Mute / unmute the microphone */

/* Code 255 is reserved for special needs of AT keyboard driver */

static const uint16_t BTN_MISC = 0x100;
static const uint16_t BTN_0 = 0x100;
static const uint16_t BTN_1 = 0x101;
static const uint16_t BTN_2 = 0x102;
static const uint16_t BTN_3 = 0x103;
static const uint16_t BTN_4 = 0x104;
static const uint16_t BTN_5 = 0x105;
static const uint16_t BTN_6 = 0x106;
static const uint16_t BTN_7 = 0x107;
static const uint16_t BTN_8 = 0x108;
static const uint16_t BTN_9 = 0x109;

static const uint16_t BTN_MOUSE = 0x110;
static const uint16_t BTN_LEFT = 0x110;
static const uint16_t BTN_RIGHT = 0x111;
static const uint16_t BTN_MIDDLE = 0x112;
static const uint16_t BTN_SIDE = 0x113;
static const uint16_t BTN_EXTRA = 0x114;
static const uint16_t BTN_FORWARD = 0x115;
static const uint16_t BTN_BACK = 0x116;
static const uint16_t BTN_TASK = 0x117;

static const uint16_t BTN_JOYSTICK = 0x120;
static const uint16_t BTN_TRIGGER = 0x120;
static const uint16_t BTN_THUMB = 0x121;
static const uint16_t BTN_THUMB2 = 0x122;
static const uint16_t BTN_TOP = 0x123;
static const uint16_t BTN_TOP2 = 0x124;
static const uint16_t BTN_PINKIE = 0x125;
static const uint16_t BTN_BASE = 0x126;
static const uint16_t BTN_BASE2 = 0x127;
static const uint16_t BTN_BASE3 = 0x128;
static const uint16_t BTN_BASE4 = 0x129;
static const uint16_t BTN_BASE5 = 0x12a;
static const uint16_t BTN_BASE6 = 0x12b;
static const uint16_t BTN_DEAD = 0x12f;

static const uint16_t BTN_GAMEPAD = 0x130;
static const uint16_t BTN_SOUTH = 0x130;
static const uint16_t BTN_A = BTN_SOUTH;
static const uint16_t BTN_EAST = 0x131;
static const uint16_t BTN_B = BTN_EAST;
static const uint16_t BTN_C = 0x132;
static const uint16_t BTN_NORTH = 0x133;
static const uint16_t BTN_X = BTN_NORTH;
static const uint16_t BTN_WEST = 0x134;
static const uint16_t BTN_Y = BTN_WEST;
static const uint16_t BTN_Z = 0x135;
static const uint16_t BTN_TL = 0x136;
static const uint16_t BTN_TR = 0x137;
static const uint16_t BTN_TL2 = 0x138;
static const uint16_t BTN_TR2 = 0x139;
static const uint16_t BTN_SELECT = 0x13a;
static const uint16_t BTN_START = 0x13b;
static const uint16_t BTN_MODE = 0x13c;
static const uint16_t BTN_THUMBL = 0x13d;
static const uint16_t BTN_THUMBR = 0x13e;

static const uint16_t BTN_DIGI = 0x140;
static const uint16_t BTN_TOOL_PEN = 0x140;
static const uint16_t BTN_TOOL_RUBBER = 0x141;
static const uint16_t BTN_TOOL_BRUSH = 0x142;
static const uint16_t BTN_TOOL_PENCIL = 0x143;
static const uint16_t BTN_TOOL_AIRBRUSH = 0x144;
static const uint16_t BTN_TOOL_FINGER = 0x145;
static const uint16_t BTN_TOOL_MOUSE = 0x146;
static const uint16_t BTN_TOOL_LENS = 0x147;
static const uint16_t BTN_TOOL_QUINTTAP = 0x148;    /* Five fingers on trackpad */
static const uint16_t BTN_TOUCH = 0x14a;
static const uint16_t BTN_STYLUS = 0x14b;
static const uint16_t BTN_STYLUS2 = 0x14c;
static const uint16_t BTN_TOOL_DOUBLETAP = 0x14d;
static const uint16_t BTN_TOOL_TRIPLETAP = 0x14e;
static const uint16_t BTN_TOOL_QUADTAP = 0x14f;    /* Four fingers on trackpad */

static const uint16_t BTN_WHEEL = 0x150;
static const uint16_t BTN_GEAR_DOWN = 0x150;
static const uint16_t BTN_GEAR_UP = 0x151;

static const uint16_t KEY_OK = 0x160;
static const uint16_t KEY_SELECT = 0x161;
static const uint16_t KEY_GOTO = 0x162;
static const uint16_t KEY_CLEAR = 0x163;
static const uint16_t KEY_POWER2 = 0x164;
static const uint16_t KEY_OPTION = 0x165;
static const uint16_t KEY_INFO = 0x166;    /* AL OEM Features/Tips/Tutorial */
static const uint16_t KEY_TIME = 0x167;
static const uint16_t KEY_VENDOR = 0x168;
static const uint16_t KEY_ARCHIVE = 0x169;
static const uint16_t KEY_PROGRAM = 0x16a;    /* Media Select Program Guide */
static const uint16_t KEY_CHANNEL = 0x16b;
static const uint16_t KEY_FAVORITES = 0x16c;
static const uint16_t KEY_EPG = 0x16d;
static const uint16_t KEY_PVR = 0x16e;    /* Media Select Home */
static const uint16_t KEY_MHP = 0x16f;
static const uint16_t KEY_LANGUAGE = 0x170;
static const uint16_t KEY_TITLE = 0x171;
static const uint16_t KEY_SUBTITLE = 0x172;
static const uint16_t KEY_ANGLE = 0x173;
static const uint16_t KEY_ZOOM = 0x174;
static const uint16_t KEY_MODE = 0x175;
static const uint16_t KEY_KEYBOARD = 0x176;
static const uint16_t KEY_SCREEN = 0x177;
static const uint16_t KEY_PC = 0x178;    /* Media Select Computer */
static const uint16_t KEY_TV = 0x179;    /* Media Select TV */
static const uint16_t KEY_TV2 = 0x17a;    /* Media Select Cable */
static const uint16_t KEY_VCR = 0x17b;    /* Media Select VCR */
static const uint16_t KEY_VCR2 = 0x17c;    /* VCR Plus */
static const uint16_t KEY_SAT = 0x17d;    /* Media Select Satellite */
static const uint16_t KEY_SAT2 = 0x17e;
static const uint16_t KEY_CD = 0x17f;    /* Media Select CD */
static const uint16_t KEY_TAPE = 0x180;    /* Media Select Tape */
static const uint16_t KEY_RADIO = 0x181;
static const uint16_t KEY_TUNER = 0x182;    /* Media Select Tuner */
static const uint16_t KEY_PLAYER = 0x183;
static const uint16_t KEY_TEXT = 0x184;
static const uint16_t KEY_DVD = 0x185;    /* Media Select DVD */
static const uint16_t KEY_AUX = 0x186;
static const uint16_t KEY_MP3 = 0x187;
static const uint16_t KEY_AUDIO = 0x188;    /* AL Audio Browser */
static const uint16_t KEY_VIDEO = 0x189;    /* AL Movie Browser */
static const uint16_t KEY_DIRECTORY = 0x18a;
static const uint16_t KEY_LIST = 0x18b;
static const uint16_t KEY_MEMO = 0x18c;    /* Media Select Messages */
static const uint16_t KEY_CALENDAR = 0x18d;
static const uint16_t KEY_RED = 0x18e;
static const uint16_t KEY_GREEN = 0x18f;
static const uint16_t KEY_YELLOW = 0x190;
static const uint16_t KEY_BLUE = 0x191;
static const uint16_t KEY_CHANNELUP = 0x192;    /* Channel Increment */
static const uint16_t KEY_CHANNELDOWN = 0x193;    /* Channel Decrement */
static const uint16_t KEY_FIRST = 0x194;
static const uint16_t KEY_LAST = 0x195;    /* Recall Last */
static const uint16_t KEY_AB = 0x196;
static const uint16_t KEY_NEXT = 0x197;
static const uint16_t KEY_RESTART = 0x198;
static const uint16_t KEY_SLOW = 0x199;
static const uint16_t KEY_SHUFFLE = 0x19a;
static const uint16_t KEY_BREAK = 0x19b;
static const uint16_t KEY_PREVIOUS = 0x19c;
static const uint16_t KEY_DIGITS = 0x19d;
static const uint16_t KEY_TEEN = 0x19e;
static const uint16_t KEY_TWEN = 0x19f;
static const uint16_t KEY_VIDEOPHONE = 0x1a0;    /* Media Select Video Phone */
static const uint16_t KEY_GAMES = 0x1a1;    /* Media Select Games */
static const uint16_t KEY_ZOOMIN = 0x1a2;    /* AC Zoom In */
static const uint16_t KEY_ZOOMOUT = 0x1a3;    /* AC Zoom Out */
static const uint16_t KEY_ZOOMRESET = 0x1a4;    /* AC Zoom */
static const uint16_t KEY_WORDPROCESSOR = 0x1a5;    /* AL Word Processor */
static const uint16_t KEY_EDITOR = 0x1a6;    /* AL Text Editor */
static const uint16_t KEY_SPREADSHEET = 0x1a7;    /* AL Spreadsheet */
static const uint16_t KEY_GRAPHICSEDITOR = 0x1a8;    /* AL Graphics Editor */
static const uint16_t KEY_PRESENTATION = 0x1a9;    /* AL Presentation App */
static const uint16_t KEY_DATABASE = 0x1aa;    /* AL Database App */
static const uint16_t KEY_NEWS = 0x1ab;    /* AL Newsreader */
static const uint16_t KEY_VOICEMAIL = 0x1ac;    /* AL Voicemail */
static const uint16_t KEY_ADDRESSBOOK = 0x1ad;    /* AL Contacts/Address Book */
static const uint16_t KEY_MESSENGER = 0x1ae;    /* AL Instant Messaging */
static const uint16_t KEY_DISPLAYTOGGLE = 0x1af;    /* Turn display (LCD) on and off */
static const uint16_t KEY_BRIGHTNESS_TOGGLE = KEY_DISPLAYTOGGLE;
static const uint16_t KEY_SPELLCHECK = 0x1b0;   /* AL Spell Check */
static const uint16_t KEY_LOGOFF = 0x1b1;   /* AL Logoff */

static const uint16_t KEY_DOLLAR = 0x1b2;
static const uint16_t KEY_EURO = 0x1b3;

static const uint16_t KEY_FRAMEBACK = 0x1b4;    /* Consumer - transport controls */
static const uint16_t KEY_FRAMEFORWARD = 0x1b5;
static const uint16_t KEY_CONTEXT_MENU = 0x1b6;    /* GenDesc - system context menu */
static const uint16_t KEY_MEDIA_REPEAT = 0x1b7;    /* Consumer - transport control */
static const uint16_t KEY_10CHANNELSUP = 0x1b8;    /* 10 channels up (10+) */
static const uint16_t KEY_10CHANNELSDOWN = 0x1b9;    /* 10 channels down (10-) */
static const uint16_t KEY_IMAGES = 0x1ba;    /* AL Image Browser */

static const uint16_t KEY_DEL_EOL = 0x1c0;
static const uint16_t KEY_DEL_EOS = 0x1c1;
static const uint16_t KEY_INS_LINE = 0x1c2;
static const uint16_t KEY_DEL_LINE = 0x1c3;

static const uint16_t KEY_FN = 0x1d0;
static const uint16_t KEY_FN_ESC = 0x1d1;
static const uint16_t KEY_FN_F1 = 0x1d2;
static const uint16_t KEY_FN_F2 = 0x1d3;
static const uint16_t KEY_FN_F3 = 0x1d4;
static const uint16_t KEY_FN_F4 = 0x1d5;
static const uint16_t KEY_FN_F5 = 0x1d6;
static const uint16_t KEY_FN_F6 = 0x1d7;
static const uint16_t KEY_FN_F7 = 0x1d8;
static const uint16_t KEY_FN_F8 = 0x1d9;
static const uint16_t KEY_FN_F9 = 0x1da;
static const uint16_t KEY_FN_F10 = 0x1db;
static const uint16_t KEY_FN_F11 = 0x1dc;
static const uint16_t KEY_FN_F12 = 0x1dd;
static const uint16_t KEY_FN_1 = 0x1de;
static const uint16_t KEY_FN_2 = 0x1df;
static const uint16_t KEY_FN_D = 0x1e0;
static const uint16_t KEY_FN_E = 0x1e1;
static const uint16_t KEY_FN_F = 0x1e2;
static const uint16_t KEY_FN_S = 0x1e3;
static const uint16_t KEY_FN_B = 0x1e4;

static const uint16_t KEY_BRL_DOT1 = 0x1f1;
static const uint16_t KEY_BRL_DOT2 = 0x1f2;
static const uint16_t KEY_BRL_DOT3 = 0x1f3;
static const uint16_t KEY_BRL_DOT4 = 0x1f4;
static const uint16_t KEY_BRL_DOT5 = 0x1f5;
static const uint16_t KEY_BRL_DOT6 = 0x1f6;
static const uint16_t KEY_BRL_DOT7 = 0x1f7;
static const uint16_t KEY_BRL_DOT8 = 0x1f8;
static const uint16_t KEY_BRL_DOT9 = 0x1f9;
static const uint16_t KEY_BRL_DOT10 = 0x1fa;

static const uint16_t KEY_NUMERIC_0 = 0x200;    /* used by phones, remote controls, */
static const uint16_t KEY_NUMERIC_1 = 0x201;    /* and other keypads */
static const uint16_t KEY_NUMERIC_2 = 0x202;
static const uint16_t KEY_NUMERIC_3 = 0x203;
static const uint16_t KEY_NUMERIC_4 = 0x204;
static const uint16_t KEY_NUMERIC_5 = 0x205;
static const uint16_t KEY_NUMERIC_6 = 0x206;
static const uint16_t KEY_NUMERIC_7 = 0x207;
static const uint16_t KEY_NUMERIC_8 = 0x208;
static const uint16_t KEY_NUMERIC_9 = 0x209;
static const uint16_t KEY_NUMERIC_STAR = 0x20a;
static const uint16_t KEY_NUMERIC_POUND = 0x20b;
static const uint16_t KEY_NUMERIC_A = 0x20c;    /* Phone key A - HUT Telephony 0xb9 */
static const uint16_t KEY_NUMERIC_B = 0x20d;
static const uint16_t KEY_NUMERIC_C = 0x20e;
static const uint16_t KEY_NUMERIC_D = 0x20f;

static const uint16_t KEY_CAMERA_FOCUS = 0x210;
static const uint16_t KEY_WPS_BUTTON = 0x211;    /* WiFi Protected Setup key */

static const uint16_t KEY_TOUCHPAD_TOGGLE = 0x212;    /* Request switch touchpad on or off */
static const uint16_t KEY_TOUCHPAD_ON = 0x213;
static const uint16_t KEY_TOUCHPAD_OFF = 0x214;

static const uint16_t KEY_CAMERA_ZOOMIN = 0x215;
static const uint16_t KEY_CAMERA_ZOOMOUT = 0x216;
static const uint16_t KEY_CAMERA_UP = 0x217;
static const uint16_t KEY_CAMERA_DOWN = 0x218;
static const uint16_t KEY_CAMERA_LEFT = 0x219;
static const uint16_t KEY_CAMERA_RIGHT = 0x21a;

static const uint16_t KEY_ATTENDANT_ON = 0x21b;
static const uint16_t KEY_ATTENDANT_OFF = 0x21c;
static const uint16_t KEY_ATTENDANT_TOGGLE = 0x21d;    /* Attendant call on or off */
static const uint16_t KEY_LIGHTS_TOGGLE = 0x21e;    /* Reading light on or off */

static const uint16_t BTN_DPAD_UP = 0x220;
static const uint16_t BTN_DPAD_DOWN = 0x221;
static const uint16_t BTN_DPAD_LEFT = 0x222;
static const uint16_t BTN_DPAD_RIGHT = 0x223;

static const uint16_t KEY_ALS_TOGGLE = 0x230;    /* Ambient light sensor */

static const uint16_t KEY_BUTTONCONFIG = 0x240;    /* AL Button Configuration */
static const uint16_t KEY_TASKMANAGER = 0x241;    /* AL Task/Project Manager */
static const uint16_t KEY_JOURNAL = 0x242;    /* AL Log/Journal/Timecard */
static const uint16_t KEY_CONTROLPANEL = 0x243;    /* AL Control Panel */
static const uint16_t KEY_APPSELECT = 0x244;    /* AL Select Task/Application */
static const uint16_t KEY_SCREENSAVER = 0x245;    /* AL Screen Saver */
static const uint16_t KEY_VOICECOMMAND = 0x246;    /* Listening Voice Command */

static const uint16_t KEY_BRIGHTNESS_MIN = 0x250;    /* Set Brightness to Minimum */
static const uint16_t KEY_BRIGHTNESS_MAX = 0x251;    /* Set Brightness to Maximum */

static const uint16_t KEY_KBDINPUTASSIST_PREV = 0x260;
static const uint16_t KEY_KBDINPUTASSIST_NEXT = 0x261;
static const uint16_t KEY_KBDINPUTASSIST_PREVGROUP = 0x262;
static const uint16_t KEY_KBDINPUTASSIST_NEXTGROUP = 0x263;
static const uint16_t KEY_KBDINPUTASSIST_ACCEPT = 0x264;
static const uint16_t KEY_KBDINPUTASSIST_CANCEL = 0x265;

/* Diagonal movement keys */
static const uint16_t KEY_RIGHT_UP = 0x266;
static const uint16_t KEY_RIGHT_DOWN = 0x267;
static const uint16_t KEY_LEFT_UP = 0x268;
static const uint16_t KEY_LEFT_DOWN = 0x269;

static const uint16_t KEY_ROOT_MENU = 0x26a; /* Show Device's Root Menu */
/* Show Top Menu of the Media (e.g. DVD) */
static const uint16_t KEY_MEDIA_TOP_MENU = 0x26b;
static const uint16_t KEY_NUMERIC_11 = 0x26c;
static const uint16_t KEY_NUMERIC_12 = 0x26d;
/*
 * Toggle Audio Description: refers to an audio service that helps blind and
 * visually impaired consumers understand the action in a program. Note: in
 * some countries this is referred to as "Video Description".
 */
static const uint16_t KEY_AUDIO_DESC = 0x26e;
static const uint16_t KEY_3D_MODE = 0x26f;
static const uint16_t KEY_NEXT_FAVORITE = 0x270;
static const uint16_t KEY_STOP_RECORD = 0x271;
static const uint16_t KEY_PAUSE_RECORD = 0x272;
static const uint16_t KEY_VOD = 0x273; /* Video on Demand */
static const uint16_t KEY_UNMUTE = 0x274;
static const uint16_t KEY_FASTREVERSE = 0x275;
static const uint16_t KEY_SLOWREVERSE = 0x276;
/*
 * Control a data application associated with the currently viewed channel,
 * e.g. teletext or data broadcast application (MHEG, MHP, HbbTV, etc.)
 */
static const uint16_t KEY_DATA = 0x277;

static const uint16_t BTN_TRIGGER_HAPPY = 0x2c0;
static const uint16_t BTN_TRIGGER_HAPPY1 = 0x2c0;
static const uint16_t BTN_TRIGGER_HAPPY2 = 0x2c1;
static const uint16_t BTN_TRIGGER_HAPPY3 = 0x2c2;
static const uint16_t BTN_TRIGGER_HAPPY4 = 0x2c3;
static const uint16_t BTN_TRIGGER_HAPPY5 = 0x2c4;
static const uint16_t BTN_TRIGGER_HAPPY6 = 0x2c5;
static const uint16_t BTN_TRIGGER_HAPPY7 = 0x2c6;
static const uint16_t BTN_TRIGGER_HAPPY8 = 0x2c7;
static const uint16_t BTN_TRIGGER_HAPPY9 = 0x2c8;
static const uint16_t BTN_TRIGGER_HAPPY10 = 0x2c9;
static const uint16_t BTN_TRIGGER_HAPPY11 = 0x2ca;
static const uint16_t BTN_TRIGGER_HAPPY12 = 0x2cb;
static const uint16_t BTN_TRIGGER_HAPPY13 = 0x2cc;
static const uint16_t BTN_TRIGGER_HAPPY14 = 0x2cd;
static const uint16_t BTN_TRIGGER_HAPPY15 = 0x2ce;
static const uint16_t BTN_TRIGGER_HAPPY16 = 0x2cf;
static const uint16_t BTN_TRIGGER_HAPPY17 = 0x2d0;
static const uint16_t BTN_TRIGGER_HAPPY18 = 0x2d1;
static const uint16_t BTN_TRIGGER_HAPPY19 = 0x2d2;
static const uint16_t BTN_TRIGGER_HAPPY20 = 0x2d3;
static const uint16_t BTN_TRIGGER_HAPPY21 = 0x2d4;
static const uint16_t BTN_TRIGGER_HAPPY22 = 0x2d5;
static const uint16_t BTN_TRIGGER_HAPPY23 = 0x2d6;
static const uint16_t BTN_TRIGGER_HAPPY24 = 0x2d7;
static const uint16_t BTN_TRIGGER_HAPPY25 = 0x2d8;
static const uint16_t BTN_TRIGGER_HAPPY26 = 0x2d9;
static const uint16_t BTN_TRIGGER_HAPPY27 = 0x2da;
static const uint16_t BTN_TRIGGER_HAPPY28 = 0x2db;
static const uint16_t BTN_TRIGGER_HAPPY29 = 0x2dc;
static const uint16_t BTN_TRIGGER_HAPPY30 = 0x2dd;
static const uint16_t BTN_TRIGGER_HAPPY31 = 0x2de;
static const uint16_t BTN_TRIGGER_HAPPY32 = 0x2df;
static const uint16_t BTN_TRIGGER_HAPPY33 = 0x2e0;
static const uint16_t BTN_TRIGGER_HAPPY34 = 0x2e1;
static const uint16_t BTN_TRIGGER_HAPPY35 = 0x2e2;
static const uint16_t BTN_TRIGGER_HAPPY36 = 0x2e3;
static const uint16_t BTN_TRIGGER_HAPPY37 = 0x2e4;
static const uint16_t BTN_TRIGGER_HAPPY38 = 0x2e5;
static const uint16_t BTN_TRIGGER_HAPPY39 = 0x2e6;
static const uint16_t BTN_TRIGGER_HAPPY40 = 0x2e7;

/* We avoid low common keys in module aliases so they don't get huge. */
static const uint16_t KEY_MIN_INTERESTING = KEY_MUTE;
static const uint16_t KEY_MAX = 0x2ff;
static const uint16_t KEY_CNT = (KEY_MAX+1);

/*
 * Relative axes
 */

static const uint16_t REL_X = 0x00;
static const uint16_t REL_Y = 0x01;
static const uint16_t REL_Z = 0x02;
static const uint16_t REL_RX = 0x03;
static const uint16_t REL_RY = 0x04;
static const uint16_t REL_RZ = 0x05;
static const uint16_t REL_HWHEEL = 0x06;
static const uint16_t REL_DIAL = 0x07;
static const uint16_t REL_WHEEL = 0x08;
static const uint16_t REL_MISC = 0x09;
static const uint16_t REL_MAX = 0x0f;
static const uint16_t REL_CNT = (REL_MAX+1);

/*
 * Absolute axes
 */

static const uint16_t ABS_X = 0x00;
static const uint16_t ABS_Y = 0x01;
static const uint16_t ABS_Z = 0x02;
static const uint16_t ABS_RX = 0x03;
static const uint16_t ABS_RY = 0x04;
static const uint16_t ABS_RZ = 0x05;
static const uint16_t ABS_THROTTLE = 0x06;
static const uint16_t ABS_RUDDER = 0x07;
static const uint16_t ABS_WHEEL = 0x08;
static const uint16_t ABS_GAS = 0x09;
static const uint16_t ABS_BRAKE = 0x0a;
static const uint16_t ABS_HAT0X = 0x10;
static const uint16_t ABS_HAT0Y = 0x11;
static const uint16_t ABS_HAT1X = 0x12;
static const uint16_t ABS_HAT1Y = 0x13;
static const uint16_t ABS_HAT2X = 0x14;
static const uint16_t ABS_HAT2Y = 0x15;
static const uint16_t ABS_HAT3X = 0x16;
static const uint16_t ABS_HAT3Y = 0x17;
static const uint16_t ABS_PRESSURE = 0x18;
static const uint16_t ABS_DISTANCE = 0x19;
static const uint16_t ABS_TILT_X = 0x1a;
static const uint16_t ABS_TILT_Y = 0x1b;
static const uint16_t ABS_TOOL_WIDTH = 0x1c;

static const uint16_t ABS_VOLUME = 0x20;

static const uint16_t ABS_MISC = 0x28;

static const uint16_t ABS_MT_SLOT = 0x2f;    /* MT slot being modified */
static const uint16_t ABS_MT_TOUCH_MAJOR = 0x30;    /* Major axis of touching ellipse */
static const uint16_t ABS_MT_TOUCH_MINOR = 0x31;    /* Minor axis (omit if circular) */
static const uint16_t ABS_MT_WIDTH_MAJOR = 0x32;    /* Major axis of approaching ellipse */
static const uint16_t ABS_MT_WIDTH_MINOR = 0x33;    /* Minor axis (omit if circular) */
static const uint16_t ABS_MT_ORIENTATION = 0x34;    /* Ellipse orientation */
static const uint16_t ABS_MT_POSITION_X = 0x35;    /* Center X touch position */
static const uint16_t ABS_MT_POSITION_Y = 0x36;    /* Center Y touch position */
static const uint16_t ABS_MT_TOOL_TYPE = 0x37;    /* Type of touching device */
static const uint16_t ABS_MT_BLOB_ID = 0x38;    /* Group a set of packets as a blob */
static const uint16_t ABS_MT_TRACKING_ID = 0x39;    /* Unique ID of initiated contact */
static const uint16_t ABS_MT_PRESSURE = 0x3a;    /* Pressure on contact area */
static const uint16_t ABS_MT_DISTANCE = 0x3b;    /* Contact hover distance */
static const uint16_t ABS_MT_TOOL_X = 0x3c;    /* Center X tool position */
static const uint16_t ABS_MT_TOOL_Y = 0x3d;    /* Center Y tool position */


static const uint16_t ABS_MAX = 0x3f;
static const uint16_t ABS_CNT = (ABS_MAX+1);

/*
 * Switch events
 */

static const uint16_t SW_LID = 0x00;  /* set = lid shut */
static const uint16_t SW_TABLET_MODE = 0x01;  /* set = tablet mode */
static const uint16_t SW_HEADPHONE_INSERT = 0x02;  /* set = inserted */
static const uint16_t SW_RFKILL_ALL = 0x03;  /* rfkill master switch, type "any"
					 set = radio enabled */
static const uint16_t SW_RADIO = SW_RFKILL_ALL;    /* deprecated */
static const uint16_t SW_MICROPHONE_INSERT = 0x04;  /* set = inserted */
static const uint16_t SW_DOCK = 0x05;  /* set = plugged into dock */
static const uint16_t SW_LINEOUT_INSERT = 0x06;  /* set = inserted */
static const uint16_t SW_JACK_PHYSICAL_INSERT = 0x07;  /* set = mechanical switch set */
static const uint16_t SW_VIDEOOUT_INSERT = 0x08;  /* set = inserted */
static const uint16_t SW_CAMERA_LENS_COVER = 0x09;  /* set = lens covered */
static const uint16_t SW_KEYPAD_SLIDE = 0x0a;  /* set = keypad slide out */
static const uint16_t SW_FRONT_PROXIMITY = 0x0b;  /* set = front proximity sensor active */
static const uint16_t SW_ROTATE_LOCK = 0x0c;  /* set = rotate locked/disabled */
static const uint16_t SW_LINEIN_INSERT = 0x0d;  /* set = inserted */
static const uint16_t SW_MUTE_DEVICE = 0x0e;  /* set = device disabled */
static const uint16_t SW_PEN_INSERTED = 0x0f;  /* set = pen inserted */
static const uint16_t SW_MAX = 0x0f;
static const uint16_t SW_CNT = (SW_MAX+1);

/*
 * Misc events
 */

static const uint16_t MSC_SERIAL = 0x00;
static const uint16_t MSC_PULSELED = 0x01;
static const uint16_t MSC_GESTURE = 0x02;
static const uint16_t MSC_RAW = 0x03;
static const uint16_t MSC_SCAN = 0x04;
static const uint16_t MSC_TIMESTAMP = 0x05;
static const uint16_t MSC_MAX = 0x07;
static const uint16_t MSC_CNT = (MSC_MAX+1);

/*
 * LEDs
 */

static const uint16_t LED_NUML = 0x00;
static const uint16_t LED_CAPSL = 0x01;
static const uint16_t LED_SCROLLL = 0x02;
static const uint16_t LED_COMPOSE = 0x03;
static const uint16_t LED_KANA = 0x04;
static const uint16_t LED_SLEEP = 0x05;
static const uint16_t LED_SUSPEND = 0x06;
static const uint16_t LED_MUTE = 0x07;
static const uint16_t LED_MISC = 0x08;
static const uint16_t LED_MAIL = 0x09;
static const uint16_t LED_CHARGING = 0x0a;
static const uint16_t LED_MAX = 0x0f;
static const uint16_t LED_CNT = (LED_MAX+1);

/*
 * Autorepeat values
 */

static const uint16_t REP_DELAY = 0x00;
static const uint16_t REP_PERIOD = 0x01;
static const uint16_t REP_MAX = 0x01;
static const uint16_t REP_CNT = (REP_MAX+1);

/*
 * Sounds
 */

static const uint16_t SND_CLICK = 0x00;
static const uint16_t SND_BELL = 0x01;
static const uint16_t SND_TONE = 0x02;
static const uint16_t SND_MAX = 0x07;
static const uint16_t SND_CNT = (SND_MAX+1);

#endif //CONTROLBLOCKSERVICE2_UINPUTEVENTCODES_H
