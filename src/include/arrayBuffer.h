#pragma once

#include <vector>
#include <glad/glad.h>

class ArrayBuffer
{
public:
	GLuint id;
	explicit ArrayBuffer(std::vector<GLuint> &);

	void bind() const;
	static void unbind();
	void destroy();
};
