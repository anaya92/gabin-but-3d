#include "rendertexture2d.h"

#include <iostream>
#include <glad/glad.h>

static std::string rt_vertshade = \
R"(#version 330 core

layout (location = 0) in vec2 xy;
layout (location = 1) in vec2 st;

out vec2 coords;

void main()
{
	coords = st;
	gl_Position = vec4(xy.x, xy.y, 0.0, 1.0); 
}
)";

static std::string rt_fragshade = \
R"(#version 330 core

out vec4 FragColor;

in vec2 coords;
uniform sampler2D rt;

void main()
{
	FragColor = texture(rt, coords);
}
)";

// full screen render
// triangle one
std::vector<rt_vertex> vertex_data = {
	{ 1.0f,  1.0f, 1.0f, 1.0f },
	{ 1.0f, -1.0f, 1.0f, 0.0f },
	{ -1.0f, -1.0f, 0.0f, 0.0f },
	{ -1.0f,  1.0f, 0.0f, 1.0f }
};

std::vector<unsigned int> index_data = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

std::vector<VertexAttributes> attr = {
	{ 2, GL_FLOAT, GL_TRUE, 4 * sizeof(float), 0 },
	{ 2, GL_FLOAT, GL_TRUE, 4 * sizeof(float), 2 * sizeof(float) }
};

RenderTexture2D::RenderTexture2D(int width, int height) : width(width), height(height), buffer(vertex_data, index_data, attr)
{
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glGenTextures(1, &Texture);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Texture, 0);

	glGenRenderbuffers(1, &RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) std::cout << "WARNING: framebuffer creation error!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

RenderTexture2D::~RenderTexture2D()
{
	glDeleteRenderbuffers(1, &RBO);
	glDeleteTextures(1, &Texture);
	glDeleteFramebuffers(1, &FBO);
}

void RenderTexture2D::start_drawing()
{
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
}

void RenderTexture2D::finish_drawing(Core* core, Shader& shader)
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader.use();
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, Texture);
	auto win_size = core->get_window_dimensions();
	glViewport(0, 0, win_size.x, win_size.y);
	buffer.draw();
}

void RenderTexture2D::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Shader RenderTexture2D::create_default_shader()
{
	return Shader(rt_vertshade, rt_fragshade);
}

