#pragma once

#include <glad/glad.h>
#include "VertexBuffer.h"

class ArrayObject
{
public:
	 /// <summary>
	 /// A unique identifier for the array object
	 /// </summary>
	 GLuint ID;

	 /// <summary>
	 /// Creates an Array Object
	 /// </summary>
	 ArrayObject();

	 /// <summary>
	 /// Links the array object to the layout
	 /// </summary>
	 /// <param name="object">The array object to be linked</param>
	 /// <param name="layout">The layout value</param>
	 void LinkObject(VertexBuffer object, GLuint layout);

	 /// <summary>
	 /// Bind the Array Object
	 /// </summary>
	 void Bind();

	 /// <summary>
	 /// Unbind the Array Object
	 /// </summary>
	 void Unbind();

	 /// <summary>
	 /// Destroy the Array Object
	 /// </summary>
	 void Destroy();
};