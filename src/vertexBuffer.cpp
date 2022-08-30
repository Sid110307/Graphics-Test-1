#include "vertexBuffer.h"

VertexBuffer::VertexBuffer(GLfloat* vertices, GLsizeiptr size) : ID(0)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Destroy()
{
	glDeleteBuffers(1, &ID);
}
