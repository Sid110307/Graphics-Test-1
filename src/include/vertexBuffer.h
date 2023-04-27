#pragma once

#include <glad/glad.h>

class VertexBuffer
{
public:
	GLuint id;
	VertexBuffer(GLfloat*, long);

	void bind() const;
	void unbind();
	void destroy();
};
