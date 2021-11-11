#pragma once

#include <array>
#include <glm/common.hpp>

struct Key
{
	bool down = false;

	enum
	{
		Unknown = -1,
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		ForwardSlash = 47, /* / */
		Keyboard0 = 48,
		Keyboard1 = 49,
		Keyboard2 = 50,
		Keyboard3 = 51,
		Keyboard4 = 52,
		Keyboard5 = 53,
		Keyboard6 = 54,
		Keyboard7 = 55,
		Keyboard8 = 56,
		Keyboard9 = 57,
		Semicolon = 59, /* ; */
		Equal = 61, /* = */
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		LeftBracket = 91, /* [ */
		Backslash = 92, /* \ */
		RightBracket = 93, /* ] */
		GraveAccent = 96, /* ` */
		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrtSc = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,
		Keypad0 = 320,
		Keypad1 = 321,
		Keypad2 = 322,
		Keypad3 = 323,
		Keypad4 = 324,
		Keypad5 = 325,
		Keypad6 = 326,
		Keypad7 = 327,
		Keypad8 = 328,
		Keypad9 = 329,
		KeypadDecimal = 330,
		KeypadDivide = 331,
		KeypadMultiply = 332,
		KeypadSubtract = 333,
		KeypadAdd = 334,
		KeypadEnter = 335,
		KeypadEqual = 336,
		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightCtrl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348,
		Count
	};
};

struct MouseButton
{
	bool down = false;

	enum
	{
		Button1,
		Button2,
		Button3,
		Button4,
		Button5,
		Button6,
		Button7,
		Button8,
		Count,
		LeftButton = Button1,
		RightButton = Button2,
		MiddleButton = Button3
	};
};

class InputManager
{
public:
	glm::vec2 get_mouse_pos();
	MouseButton get_mouseb(int button);
	Key get_key(int key);
public:
	static void connect_to_glfw(void* handle);
private:
	static std::array<MouseButton, MouseButton::Count> mousebuttons;
	static std::array<Key, Key::Count> keys;
	static glm::vec2 mouse_pos;
private:
	static void keyboard_callback(void* window, int key, int scancode, int action, int mods);
	static void mouse_position_callback(void* window, double x, double y);
	static void mousebutton_callback(void* window, int button, int action, int mods);
};
