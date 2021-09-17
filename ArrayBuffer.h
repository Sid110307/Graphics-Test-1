#pragma once
#include <glad/glad.h>

class ArrayBuffer
{
public:
	 /// <summary>
	 /// A unique identifier for the array
	 /// </summary>
	 GLuint ID;

	 /// <summary>
	 /// Creates an array with a given amount of indices and a size
	 /// </summary>
	 /// <param name="indices">Amount of indices</param>
	 /// <param name="size">Buffer size</param>
	 ArrayBuffer(GLuint* indices, GLsizeiptr size);

	 /// <summary>
	 /// Bind the Array Buffer
	 /// </summary>
	 void Bind();

	 /// <summary>
	 /// Unbind the Array Buffer
	 /// </summary>
	 void Unbind();

	 /// <summary>
	 /// Destroy the Array Buffer
	 /// </summary>
	 void Destroy();
};