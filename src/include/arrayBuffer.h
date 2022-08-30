#pragma once

#include <glad/glad.h>

class ArrayBuffer
{
public:
	GLuint ID;
	ArrayBuffer(GLuint*, long);

	void Bind() const;
	void Unbind();
	void Destroy();
};
