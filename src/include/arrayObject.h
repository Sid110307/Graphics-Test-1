#pragma once

#include <glad/glad.h>
#include "vertexBuffer.h"

class ArrayObject
{
public:
	GLuint id;

	ArrayObject();
	static void linkAttribute(VertexBuffer, GLuint, GLint, GLenum, GLint, void*);

	void bind() const;
	static void unbind();
	void destroy();
};
