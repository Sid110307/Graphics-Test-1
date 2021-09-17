#pragma once
#include <glad/glad.h>

/// <summary>
/// Vertex Buffer
/// </summary>
class VertexBuffer
{
public:
	 /// <summary>
	 /// A unique identifier for the vertex buffer
	 /// </summary>
	 GLuint ID;

	 /// <summary>
	 /// Creates a vertex with a given amount of vertices and a size
	 /// </summary>
	 /// <param name="vertices">Amount of vertices</param>
	 /// <param name="size">Buffer size</param>
	 VertexBuffer(GLfloat* vertices, GLsizeiptr size);

	 /// <summary>
	 /// Bind the Vertex
	 /// </summary>
	 void Bind();

	 /// <summary>
	 /// Unbind the Vertex
	 /// </summary>
	 void Unbind();

	 /// <summary>
	 /// Destroy the Vertex
	 /// </summary>
	 void Destroy();
};