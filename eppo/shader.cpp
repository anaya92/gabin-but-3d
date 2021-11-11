#include "shader.h"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

static void validate_shader(unsigned int id)
{
	int  success;
	char info_log[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(id, 512, NULL, info_log);
		std::cout << "shader compilation failed!\n" << info_log << std::endl;
	}
}

static void validate_program(unsigned int id)
{
	int  success;
	char info_log[512];

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) 
	{
		glGetProgramInfoLog(id, 512, NULL, info_log);
		std::cout << "program link failed!\n" << info_log << std::endl;
	}
}

Shader::Shader(std::string vert_source, std::string frag_source)
{
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertex_source_gl = vert_source.c_str();
	glShaderSource(vertex_shader, 1, &vertex_source_gl, NULL);
	glCompileShader(vertex_shader);
	validate_shader(vertex_shader);

	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragment_source_gl = frag_source.c_str();
	glShaderSource(fragment_shader, 1, &fragment_source_gl, NULL);
	glCompileShader(fragment_shader);
	validate_shader(fragment_shader);

	ID = glCreateProgram();
	glAttachShader(ID, vertex_shader);
	glAttachShader(ID, fragment_shader);
	glLinkProgram(ID);

	validate_program(ID);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::set_uniform(std::string name, float val)
{
	glUniform1f(get_uniform(name), val);
}

void Shader::set_uniform(std::string name, bool val)
{
	glUniform1i(get_uniform(name), (int) val);
}

void Shader::set_uniform(std::string name, int val)
{
	glUniform1i(get_uniform(name), val);
}

void Shader::set_uniform(std::string name, glm::mat4& val)
{
	glUniformMatrix4fv(get_uniform(name), 1, GL_FALSE, glm::value_ptr(val));
}

int Shader::get_uniform(std::string name)
{
	int result = glGetUniformLocation(ID, name.c_str());
	if (result == -1) std::cout << "uniform not found: " << name << std::endl;
	return result;
}
