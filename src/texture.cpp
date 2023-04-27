#include "include/texture.h"

Texture::Texture(const GLchar* image, GLenum _textureType, GLenum slot,
				 GLenum format, GLenum pixelType)
{
	textureType = _textureType;

	GLint width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(image, &width, &height, &channels, 0);

	glGenTextures(1, &id);
	glActiveTexture(slot);
	glBindTexture(_textureType, id);

	glTexParameteri(_textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(_textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(_textureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(_textureType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(_textureType, 0, GL_RGBA, width, height, 0, format, pixelType,
				 data);
	glGenerateMipmap(_textureType);

	stbi_image_free(data);
	glBindTexture(_textureType, 0);
}

void Texture::textureUnit(Shader &shader, const GLchar* uniform, GLuint unit)
{
	GLuint textureUniform = glGetUniformLocation(shader.id, uniform);

	shader.activate();
	glUniform1i(textureUniform, unit);
}

void Texture::bind()
{
	glBindTexture(textureType, id);
}

void Texture::unbind()
{
	glBindTexture(textureType, 0);
}

void Texture::destroy()
{
	glDeleteTextures(1, &id);
}
