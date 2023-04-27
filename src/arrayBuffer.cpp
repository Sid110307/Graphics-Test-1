#include "include/arrayBuffer.h"

ArrayBuffer::ArrayBuffer(GLuint* indices, GLsizeiptr size) : id(0)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void ArrayBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ArrayBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ArrayBuffer::destroy()
{
	glDeleteBuffers(1, &id);
}
