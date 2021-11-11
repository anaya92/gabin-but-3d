#pragma once

#include <utility>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>

#include "input.h"

class Core
{
public:
	Core();
	~Core();

	bool valid();
	void invalidate();
	void update();
	void present();
	int fps();
	double get_delta();
	void cursor_locked(bool locked);
	glm::vec2 get_window_dimensions();
public:
	InputManager input_manager;
private:
	// mouse
	glm::vec2 mouse_position;
	glm::vec2 mouse_old;

	GLFWwindow* window;
	int frames = 0;
	double current_time = 0.0;
	double last_time = 0.0;
	double last_time2 = 0.0;
	double delta = 0.0;
};