#pragma once

#include <glad/glad.h>
#include <stb/stb_image.h>

#include "shader.h"

class Texture {
public:
	GLuint ID;
	GLenum textureType;
	
	Texture(const GLchar*, GLenum, GLenum, GLenum, GLenum);
	
	void textureUnit(Shader &, const GLchar*, GLuint);
	void Bind();
	void Unbind();
	void Destroy();
};
