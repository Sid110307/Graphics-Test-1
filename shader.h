#pragma once
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

/// <summary>
/// Reads the contents of a file as a string
/// </summary>
/// <param name="filename">The path to the file</param>
/// <returns>contents: The contents of the file</returns>
std::string readFileContents(const char* filename);

/// <summary>
/// Shader Manager
/// </summary>
class Shader
{
public:
	 /// <summary>
	 /// A unique identifier for the shader program
	 /// </summary>
	 GLuint ID;

	 /// <summary>
	 /// Create a shader with a vertex file and a fragment shader
	 /// </summary>
	 /// <param name="vertexFile">The path to the vertex file</param>
	 /// <param name="fragmentFile">The path to the fragment file</param>
	 Shader(const char* vertexFile, const char* fragmentFile);

	 /// <summary>
	 /// Activates the shader
	 /// </summary>
	 void Activate();

	 /// <summary>
	 /// Deletes the shader
	 /// </summary>
	 void Destroy();
};