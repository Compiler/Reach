#pragma once
#include <stdint.h>

namespace reach {
	namespace MouseKeys {
		constexpr uint16_t MOUSE_BUTTON_1 = 0;
		constexpr uint16_t MOUSE_BUTTON_2 = 1;
		constexpr uint16_t MOUSE_BUTTON_3 = 2;
		constexpr uint16_t MOUSE_BUTTON_4 = 3;
		constexpr uint16_t MOUSE_BUTTON_5 = 4;
		constexpr uint16_t MOUSE_BUTTON_6 = 5;
		constexpr uint16_t MOUSE_BUTTON_7 = 6;
		constexpr uint16_t MOUSE_BUTTON_8 = 7;
		constexpr uint16_t MOUSE_BUTTON_LEFT = MOUSE_BUTTON_1;
		constexpr uint16_t MOUSE_BUTTON_RIGHT = MOUSE_BUTTON_2;
		constexpr uint16_t MOUSE_BUTTON_MIDDLE = MOUSE_BUTTON_3;

	}

	namespace KeyCodes {
		constexpr uint16_t KEY_SPACE = 32;
		constexpr uint16_t KEY_APOSTROPHE = 39;  /* ' */
		constexpr uint16_t KEY_COMMA = 44;  /* , */
		constexpr uint16_t KEY_MINUS = 45;  /* - */
		constexpr uint16_t KEY_PERIOD = 46;  /* . */
		constexpr uint16_t KEY_SLASH = 47;  /* / */
		constexpr uint16_t KEY_0 = 48;
		constexpr uint16_t KEY_1 = 49;
		constexpr uint16_t KEY_2 = 50;
		constexpr uint16_t KEY_3 = 51;
		constexpr uint16_t KEY_4 = 52;
		constexpr uint16_t KEY_5 = 53;
		constexpr uint16_t KEY_6 = 54;
		constexpr uint16_t KEY_7 = 55;
		constexpr uint16_t KEY_8 = 56;
		constexpr uint16_t KEY_9 = 57;
		constexpr uint16_t KEY_SEMICOLON = 59;  /* ; */
		constexpr uint16_t KEY_EQUAL = 61;  /* = */
		constexpr uint16_t KEY_A = 65;
		constexpr uint16_t KEY_B = 66;
		constexpr uint16_t KEY_C = 67;
		constexpr uint16_t KEY_D = 68;
		constexpr uint16_t KEY_E = 69;
		constexpr uint16_t KEY_F = 70;
		constexpr uint16_t KEY_G = 71;
		constexpr uint16_t KEY_H = 72;
		constexpr uint16_t KEY_I = 73;
		constexpr uint16_t KEY_J = 74;
		constexpr uint16_t KEY_K = 75;
		constexpr uint16_t KEY_L = 76;
		constexpr uint16_t KEY_M = 77;
		constexpr uint16_t KEY_N = 78;
		constexpr uint16_t KEY_O = 79;
		constexpr uint16_t KEY_P = 80;
		constexpr uint16_t KEY_Q = 81;
		constexpr uint16_t KEY_R = 82;
		constexpr uint16_t KEY_S = 83;
		constexpr uint16_t KEY_T = 84;
		constexpr uint16_t KEY_U = 85;
		constexpr uint16_t KEY_V = 86;
		constexpr uint16_t KEY_W = 87;
		constexpr uint16_t KEY_X = 88;
		constexpr uint16_t KEY_Y = 89;
		constexpr uint16_t KEY_Z = 90;
		constexpr uint16_t KEY_LEFT_BRACKET = 91;  /* [ */
		constexpr uint16_t KEY_BACKSLASH = 92;  /* \ */
		constexpr uint16_t KEY_RIGHT_BRACKET = 93;  /* ] */
		constexpr uint16_t KEY_GRAVE_ACCENT = 96;  /* ` */
		constexpr uint16_t KEY_WORLD_1 = 161; /* non-US #1 */
		constexpr uint16_t KEY_WORLD_2 = 162; /* non-US #2 */
		constexpr uint16_t KEY_ESCAPE = 256;
		constexpr uint16_t KEY_ENTER = 257;
		constexpr uint16_t KEY_TAB = 258;
		constexpr uint16_t KEY_BACKSPACE = 259;
		constexpr uint16_t KEY_INSERT = 260;
		constexpr uint16_t KEY_DELETE = 261;
		constexpr uint16_t KEY_RIGHT = 262;
		constexpr uint16_t KEY_LEFT = 263;
		constexpr uint16_t KEY_DOWN = 264;
		constexpr uint16_t KEY_UP = 265;
		constexpr uint16_t KEY_PAGE_UP = 266;
		constexpr uint16_t KEY_PAGE_DOWN = 267;
		constexpr uint16_t KEY_HOME = 268;
		constexpr uint16_t KEY_END = 269;
		constexpr uint16_t KEY_CAPS_LOCK = 280;
		constexpr uint16_t KEY_SCROLL_LOCK = 281;
		constexpr uint16_t KEY_NUM_LOCK = 282;
		constexpr uint16_t KEY_PRINT_SCREEN = 283;
		constexpr uint16_t KEY_PAUSE = 284;
		constexpr uint16_t KEY_F1 = 290;
		constexpr uint16_t KEY_F2 = 291;
		constexpr uint16_t KEY_F3 = 292;
		constexpr uint16_t KEY_F4 = 293;
		constexpr uint16_t KEY_F5 = 294;
		constexpr uint16_t KEY_F6 = 295;
		constexpr uint16_t KEY_F7 = 296;
		constexpr uint16_t KEY_F8 = 297;
		constexpr uint16_t KEY_F9 = 298;
		constexpr uint16_t KEY_F10 = 299;
		constexpr uint16_t KEY_F11 = 300;
		constexpr uint16_t KEY_F12 = 301;
		constexpr uint16_t KEY_F13 = 302;
		constexpr uint16_t KEY_F14 = 303;
		constexpr uint16_t KEY_F15 = 304;
		constexpr uint16_t KEY_F16 = 305;
		constexpr uint16_t KEY_F17 = 306;
		constexpr uint16_t KEY_F18 = 307;
		constexpr uint16_t KEY_F19 = 308;
		constexpr uint16_t KEY_F20 = 309;
		constexpr uint16_t KEY_F21 = 310;
		constexpr uint16_t KEY_F22 = 311;
		constexpr uint16_t KEY_F23 = 312;
		constexpr uint16_t KEY_F24 = 313;
		constexpr uint16_t KEY_F25 = 314;
		constexpr uint16_t KEY_KP_0 = 320;
		constexpr uint16_t KEY_KP_1 = 321;
		constexpr uint16_t KEY_KP_2 = 322;
		constexpr uint16_t KEY_KP_3 = 323;
		constexpr uint16_t KEY_KP_4 = 324;
		constexpr uint16_t KEY_KP_5 = 325;
		constexpr uint16_t KEY_KP_6 = 326;
		constexpr uint16_t KEY_KP_7 = 327;
		constexpr uint16_t KEY_KP_8 = 328;
		constexpr uint16_t KEY_KP_9 = 329;
		constexpr uint16_t KEY_KP_DECIMAL = 330;
		constexpr uint16_t KEY_KP_DIVIDE = 331;
		constexpr uint16_t KEY_KP_MULTIPLY = 332;
		constexpr uint16_t KEY_KP_SUBTRACT = 333;
		constexpr uint16_t KEY_KP_ADD = 334;
		constexpr uint16_t KEY_KP_ENTER = 335;
		constexpr uint16_t KEY_KP_EQUAL = 336;
		constexpr uint16_t KEY_LEFT_SHIFT = 340;
		constexpr uint16_t KEY_LEFT_CONTROL = 341;
		constexpr uint16_t KEY_LEFT_ALT = 342;
		constexpr uint16_t KEY_LEFT_SUPER = 343;
		constexpr uint16_t KEY_RIGHT_SHIFT = 344;
		constexpr uint16_t KEY_RIGHT_CONTROL = 345;
		constexpr uint16_t KEY_RIGHT_ALT = 346;
		constexpr uint16_t KEY_RIGHT_SUPER = 347;
		constexpr uint16_t KEY_MENU = 348;
	}
}