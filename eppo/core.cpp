#include "core.h"

#include <iostream>

static glm::vec2 mousepos;

static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	mousepos = glm::vec2(xpos, ypos);
}

Core::Core()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "gabin is out of ice cream :(", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "window creation failed\n";
	}
	glfwMakeContextCurrent(window);

	InputManager::connect_to_glfw(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "glad failed to init\n";
	}

	last_time = glfwGetTime();
	glfwSwapInterval(0);

	glViewport(0, 0, 640, 480);
}

Core::~Core()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Core::valid()
{
	return !glfwWindowShouldClose(window);
}

void Core::invalidate()
{
	glfwSetWindowShouldClose(window, 1);
}

void Core::update()
{
	current_time = glfwGetTime();
	delta = current_time - last_time2;
	last_time2 = current_time;
	frames++;
	
	if (current_time - last_time >= 1.0)
	{
		printf("%f ms/frame : fps %i\n", 1000.0 / double(frames), frames);
		frames = 0;
		last_time += 1.0;
	}

	glfwPollEvents();
}

void Core::present()
{
	glfwSwapBuffers(window);
}

double Core::get_delta()
{
	return delta;
}

void Core::cursor_locked(bool locked)
{
	glfwSetInputMode(window, GLFW_CURSOR, locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

glm::vec2 Core::get_window_dimensions()
{
	int w, h;
	glfwGetWindowSize(window, &w, &h);

	return glm::vec2(w, h);
}