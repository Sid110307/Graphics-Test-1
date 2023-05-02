#pragma once

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>

class Shader
{
public:
	GLuint id;
	Shader(const GLchar*, const GLchar*);

	void activate() const;
	void destroy() const;
private:
	static void checkCompileErrors(GLuint shader, const std::string &type);
	static const GLchar* readShader(const GLchar*);
};
