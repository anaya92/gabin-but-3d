#include "input.h"

#include <iostream>
#include <GLFW/glfw3.h>

std::array<MouseButton, MouseButton::Count> InputManager::mousebuttons;
std::array<Key, Key::Count> InputManager::keys;
glm::vec2 InputManager::mouse_pos;

glm::vec2 InputManager::get_mouse_pos()
{
	return mouse_pos;
}

MouseButton InputManager::get_mouseb(int button)
{
	return mousebuttons[button];
}

Key InputManager::get_key(int key)
{
	return keys[key];
}

void InputManager::connect_to_glfw(void* handle)
{
	GLFWwindow* window = (GLFWwindow*)handle;
	glfwSetKeyCallback(window, (GLFWkeyfun) keyboard_callback);
	glfwSetCursorPosCallback(window, (GLFWcursorposfun) mouse_position_callback);
	glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun) mousebutton_callback);
}

void InputManager::keyboard_callback(void* window, int key, int scancode, int action, int mods)
{
	keys[key].down = action != GLFW_RELEASE;
}

void InputManager::mouse_position_callback(void* window, double x, double y)
{
	mouse_pos.x = x;
	mouse_pos.y = y;
}

void InputManager::mousebutton_callback(void* window, int button, int action, int mods)
{
	mousebuttons[button].down = action == GLFW_PRESS;
}