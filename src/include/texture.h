#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "shader.h"

class Texture
{
public:
	GLuint id = 0;
	GLenum textureType;
	GLuint textureUnit;

	Texture(const GLchar*, GLenum, GLuint, GLenum, GLenum);

	static void textureUniform(Shader &shader, const GLchar* uniform, GLuint unit);
	void bind() const;
	void unbind() const;
	void destroy();
};
