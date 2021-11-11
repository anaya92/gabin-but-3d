#pragma once

#include <vector>
#include <glad/glad.h>

struct VertexAttributes
{
	int size;
	int type;
	bool normalized;
	int stride; // stride between each attribute of the same type (in bytes)
	int offset; // offset within each vertex (in bytes)
};

template <typename T> class Buffer
{
public:
	// unindexed buffer (without EBO)
	Buffer(std::vector<T> vertices, std::vector<VertexAttributes> attributes)
	{
		// gen VAO & VBO
		glGenBuffers(1, &VBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(T) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		for (int i = 0; i < attributes.size(); i++)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, attributes[i].size, attributes[i].type, attributes[i].normalized, attributes[i].stride, (void*)attributes[i].offset);
		}

		all_elements_to_draw = vertices.size();
	}

	// indexed buffer (with EBO)
	Buffer(std::vector<T> vertices, std::vector<unsigned int> indices, std::vector<VertexAttributes> attributes)
	{
		indexed = true;
		
		// gen VAO, VBO, & EBO
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenVertexArrays(1, &VAO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(T) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

		for (int i = 0; i < attributes.size(); i++)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, attributes[i].size, attributes[i].type, attributes[i].normalized, attributes[i].stride, (void*)attributes[i].offset);
		}

		all_elements_to_draw = indices.size();
	}

	~Buffer()
	{
		glDeleteBuffers(1, &VBO);
		glDeleteVertexArrays(1, &VAO);
	}

	void bind()
	{
		glBindVertexArray(VAO);
	}

	void draw()
	{
		bind();
		if (indexed)
		{
			glDrawElements(GL_TRIANGLES, all_elements_to_draw, GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, all_elements_to_draw);
		}
	}

	bool is_indexed() { return indexed; }
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO; // may be unused
	unsigned int all_elements_to_draw = 0;
	bool indexed = false;
};