#pragma once

#include <iostream>
#include <vector>
#include <glm/common.hpp>

class Shader
{
public:
	Shader(std::string vert_source, std::string frag_source);
	~Shader();
	void use();
	void set_uniform(std::string name, float val);
	void set_uniform(std::string name, bool val);
	void set_uniform(std::string name, int val);
	void set_uniform(std::string name, glm::mat4& val);
private:
	int get_uniform(std::string name);
	unsigned int ID;
};