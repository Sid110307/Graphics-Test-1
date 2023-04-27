#pragma once

#include <glad/glad.h>
#include "vertexBuffer.h"

class ArrayObject
{
public:
	GLuint id;

	ArrayObject();
	void linkAttribute(VertexBuffer, GLuint, GLint, GLenum, GLint, void*);

	void bind() const;
	void unbind();
	void destroy();
};
