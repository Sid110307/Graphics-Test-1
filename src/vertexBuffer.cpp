#include "include/vertexBuffer.h"

VertexBuffer::VertexBuffer(GLfloat* vertices, GLsizeiptr size) : id(0)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VertexBuffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::destroy()
{
	glDeleteBuffers(1, &id);
}
