#pragma once

#include <iostream>

class Texture2D
{
public:
	Texture2D(std::string path);
	~Texture2D();
	void bind();
	void gen_mipmaps();
private:
	unsigned int ID;
};