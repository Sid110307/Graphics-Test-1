#include "arrayBuffer.h"

ArrayBuffer::ArrayBuffer(GLuint* indices, GLsizeiptr size) : ID(0)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void ArrayBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void ArrayBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ArrayBuffer::Destroy()
{
	glDeleteBuffers(1, &ID);
}
