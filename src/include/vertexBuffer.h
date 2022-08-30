#pragma once

#include <glad/glad.h>

class VertexBuffer
{
public:
	GLuint ID;
	VertexBuffer(GLfloat*, long);

	void Bind() const;
	void Unbind();
	void Destroy();
};
