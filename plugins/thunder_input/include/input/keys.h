#ifndef TH_INPUT_KEYS_H_
#define TH_INPUT_KEYS_H_

#ifndef ECS_META_IMPL
#define ECS_META_IMPL EXTERN
#endif

#include <flecs.h>

/* 1:1 mapping from glfw, for now */
ECS_ENUM(KeyCode, {
  KeyCode_Unknown = -1,

  KeyCode_Space = 32,
  KeyCode_Apostrophe = 39,  /* ' */
  KeyCode_Comma = 44,       /* , */
  KeyCode_Minus = 45,       /* - */
  KeyCode_Period = 46,      /* . */
  KeyCode_Slash = 47,       /* / */

  KeyCode_0 = 48,           /* 0 */
  KeyCode_1 = 49,           /* 1 */
  KeyCode_2 = 50,           /* 2 */
  KeyCode_3 = 51,           /* 3 */
  KeyCode_4 = 52,           /* 4 */
  KeyCode_5 = 53,           /* 5 */
  KeyCode_6 = 54,           /* 6 */
  KeyCode_7 = 55,           /* 7 */
  KeyCode_8 = 56,           /* 8 */
  KeyCode_9 = 57,           /* 9 */

  KeyCode_Semicolon = 59,   /* ; */
  KeyCode_Equal = 61,       /* = */

  KeyCode_A = 65,         /* A */
  KeyCode_B = 66,           /* B */
  KeyCode_C = 67,           /* C */
  KeyCode_D = 68,           /* D */
  KeyCode_E = 69,           /* E */
  KeyCode_F = 70,           /* F */
  KeyCode_G = 71,           /* G */
  KeyCode_H = 72,           /* H */
  KeyCode_I = 73,           /* I */
  KeyCode_J = 74,           /* J */
  KeyCode_K = 75,           /* K */
  KeyCode_L = 76,           /* L */
  KeyCode_M = 77,           /* M */
  KeyCode_N = 78,           /* N */
  KeyCode_O = 79,           /* O */
  KeyCode_P = 80,           /* P */
  KeyCode_Q = 81,           /* Q */
  KeyCode_R = 82,           /* R */
  KeyCode_S = 83,           /* S */
  KeyCode_T = 84,           /* T */
  KeyCode_U = 85,           /* U */
  KeyCode_V = 86,           /* V */
  KeyCode_W = 87,           /* W */
  KeyCode_X = 88,           /* X */
  KeyCode_Y = 89,           /* Y */
  KeyCode_Z = 90,           /* Z */

  KeyCode_LeftBracket = 91,  /* [ */
  KeyCode_Backslash = 92,    /* \ */
  KeyCode_RightBracket = 93, /* ] */
  KeyCode_GraveAccent = 96,  /* ` */

  KeyCode_World_1 = 161, /* non-US #1 */
  KeyCode_World_2 = 162, /* non-US #2 */

  KeyCode_Escape = 256,
  KeyCode_Enter = 257,
  KeyCode_Tab = 258,
  KeyCode_Backspace = 259,

  KeyCode_Insert = 260,
  KeyCode_Delete = 261,
  KeyCode_Right = 262,
  KeyCode_Left = 263,
  KeyCode_Down = 264,
  KeyCode_Up = 265,

  KeyCode_PageUp = 266,
  KeyCode_PageDown = 267,
  KeyCode_Home = 268,
  KeyCode_End = 269,

  KeyCode_CapsLock = 280,
  KeyCode_ScrollLock = 281,
  KeyCode_NumLock = 282,
  KeyCode_PrintScreen = 283,
  KeyCode_Pause = 284,

  KeyCode_F1 = 290,
  KeyCode_F2 = 291,
  KeyCode_F3 = 292,
  KeyCode_F4 = 293,
  KeyCode_F5 = 294,
  KeyCode_F6 = 295,
  KeyCode_F7 = 296,
  KeyCode_F8 = 297,
  KeyCode_F9 = 298,
  KeyCode_F10 = 299,
  KeyCode_F11 = 300,
  KeyCode_F12 = 301,
  KeyCode_F13 = 302,
  KeyCode_F14 = 303,
  KeyCode_F15 = 304,
  KeyCode_F16 = 305,
  KeyCode_F17 = 306,
  KeyCode_F18 = 307,
  KeyCode_F19 = 308,
  KeyCode_F20 = 309,
  KeyCode_F21 = 310,
  KeyCode_F22 = 311,
  KeyCode_F23 = 312,
  KeyCode_F24 = 313,
  KeyCode_F25 = 314,

  KeyCode_NumPad0 = 320,
  KeyCode_NumPad1 = 321,
  KeyCode_NumPad2 = 322,
  KeyCode_NumPad3 = 323,
  KeyCode_NumPad4 = 324,
  KeyCode_NumPad5 = 325,
  KeyCode_NumPad6 = 326,
  KeyCode_NumPad7 = 327,
  KeyCode_NumPad8 = 328,
  KeyCode_NumPad9 = 329,

  KeyCode_NumPadDecimal = 330,
  KeyCode_NumPadDivide = 331,
  KeyCode_NumPadMultiply = 332,
  KeyCode_NumPadSubtract = 333,
  KeyCode_NumPadAdd = 334,

  KeyCode_NumPadEnter = 335,
  KeyCode_NumPadEqual = 336,

  KeyCode_LeftShift = 340,
  KeyCode_LeftControl = 341,
  KeyCode_LeftAlt = 342,
  KeyCode_LeftSuper = 343,

  KeyCode_RightShift = 344,
  KeyCode_RightControl = 345,
  KeyCode_RightAlt = 346,
  KeyCode_RightSuper = 347,

  KeyCode_Menu = 348,

  KeyCode_Last = KeyCode_Menu,
});

ECS_STRUCT(KeyPressed, {
  KeyCode code;
});

ECS_STRUCT(KeyReleased, {
  KeyCode code;
});

ECS_STRUCT(KeyRepeated, {
  KeyCode code;
});

#endif /* TH_INPUT_KEYS_H_ */
