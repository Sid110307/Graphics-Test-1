#include "ArrayObject.h"

ArrayObject::ArrayObject()
{
	 glGenVertexArrays(1, &ID);
}

void ArrayObject::LinkObject(VertexBuffer object, GLuint layout)
{
	 object.Bind();
	 glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	 glEnableVertexAttribArray(layout);
	 object.Unbind();
}

void ArrayObject::Bind()
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