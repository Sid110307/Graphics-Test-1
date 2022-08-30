#include "./arrayObject.h"

ArrayObject::ArrayObject() : ID(0)
{
	glGenVertexArrays(1, &ID);
}

void ArrayObject::LinkAttribute(VertexBuffer object, GLuint layout, GLint size,
								GLenum type, GLint stride, void* offset)
{
	object.Bind();

	glVertexAttribPointer(layout, size, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	object.Unbind();
}

void ArrayObject::Bind() const
{
	glBindVertexArray(ID);
}

void ArrayObject::Unbind()
{
	glBindVertexArray(0);
}

void ArrayObject::Destroy()
{
	glDeleteVertexArrays(1, &ID);
}
