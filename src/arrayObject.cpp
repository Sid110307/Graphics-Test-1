#include "include/arrayObject.h"

ArrayObject::ArrayObject() : id(0)
{
	glGenVertexArrays(1, &id);
}

void ArrayObject::linkAttribute(VertexBuffer object, GLuint layout, GLint size, GLenum type, GLint stride, void* offset)
{
	object.bind();

	glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	object.unbind();
}

void ArrayObject::bind() const
{
	glBindVertexArray(id);
}

void ArrayObject::unbind()
{
	glBindVertexArray(0);
}

void ArrayObject::destroy()
{
	glDeleteVertexArrays(1, &id);
}
