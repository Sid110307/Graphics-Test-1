#pragma once
#include <glad/glad.h>

class ArrayBuffer
{
public:
	GLuint id;
	ArrayBuffer(GLuint*, long);

	void bind() const;
	void unbind();
	void destroy();
};
