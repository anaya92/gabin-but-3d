#pragma once

#include <utility>
#include "core.h"
#include "shader.h"
#include "buffer.h"

struct rt_vertex
{
	float x, y, s, t;
};

class RenderTexture2D
{
public:
	RenderTexture2D(int width, int height);
	~RenderTexture2D();

	void start_drawing();
	void finish_drawing(Core* core, Shader& shader);
	void clear(float r, float g, float b, float a);
	Shader create_default_shader();
private:
	unsigned int FBO;
	unsigned int RBO;
	unsigned int Texture;

	int width, height;

	Buffer<rt_vertex> buffer;
};