#pragma once

#include <glad/glad.h>
#include "vertexBuffer.h"

class ArrayObject
{
public:
	GLuint ID;

	ArrayObject();
	void LinkAttribute(VertexBuffer, GLuint, GLint, GLenum, GLint, void*);

	void Bind() const;
	void Unbind();
	void Destroy();
};
