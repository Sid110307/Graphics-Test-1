#include "include/texture.h"

Texture::Texture(const GLchar* image, GLenum textureType, GLuint slot,
				 GLenum format, GLenum pixelType)
{
	this->textureType = textureType;

	GLint width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(image, &width, &height, &channels, 0);

	glGenTextures(1, &id);
	glActiveTexture(GL_TEXTURE0 + slot);
	textureUnit = slot;
	glBindTexture(textureType, id);

	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(textureType, 0, GL_RGBA, width, height, 0, format, pixelType,
				 data);
	glGenerateMipmap(textureType);

	stbi_image_free(data);
	glBindTexture(textureType, 0);
}

void Texture::textureUniform(Shader &shader, const GLchar* uniform, GLuint unit)
{
	GLuint texUniform = glGetUniformLocation(shader.id, uniform);

	shader.activate();
	glUniform1i((GLint) texUniform, (GLint) unit);
}

void Texture::bind() const
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(textureType, id);
}

void Texture::unbind() const
{
	glBindTexture(textureType, 0);
}

void Texture::destroy()
{
	glDeleteTextures(1, &id);
}
