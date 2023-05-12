#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "shader.h"

class Texture
{
public:
	GLuint id = 0;
	const char* textureType;
	GLuint textureUnit;

	Texture(const GLchar*, const char*, GLuint, GLenum, GLenum);

	static void textureUniform(Shader &shader, const GLchar* uniform, GLuint unit);
	void bind() const;
	static void unbind() ;
	void destroy();
};
