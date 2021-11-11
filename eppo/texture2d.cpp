#include "texture2d.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture2D::Texture2D(std::string path)
{
	stbi_set_flip_vertically_on_load(true);

	int width, height, channels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

	if (data)
	{
		glGenTextures(1, &ID);
		bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		if (glGetError() != GL_NO_ERROR)
		{
			std::cout << "damn. smth went wrong when loading \"" + path + "\"\n";
		}
		this->gen_mipmaps();
		stbi_image_free(data);
	}
	else
	{
		std::cout << "failed to load texture!: " + path + "\n";
	}
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &ID);
}

void Texture2D::bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture2D::gen_mipmaps()
{
	bind();
	glGenerateMipmap(GL_TEXTURE_2D);
}
