#pragma once

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>

class Shader
{
public:
	GLuint ID;
	Shader();

	void Activate() const;
	void Destroy() const;
private:
	const char* vertexSource = R"glsl(
		#version 330 core

		layout (location = 0) in vec3 position;
		layout (location = 1) in vec3 color;
		layout (location = 2) in vec2 textureCoords;

		out vec3 outputColor;
		out vec2 outputTextureCoords;
		uniform float scale;

		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;

		void main() {
			gl_Position = projection * view * model * vec4(position * scale, 1.0f);

			outputColor = color;
			outputTextureCoords = textureCoords;
		}
	)glsl";

	const char* fragmentSource = R"glsl(
		#version 330 core

		in vec3 outputColor;
		in vec2 outputTextureCoords;

		out vec4 fragmentColor;
		uniform sampler2D textureSampler;

		void main() {
			fragmentColor = texture(textureSampler, outputTextureCoords);
		}
	)glsl";

	void CheckCompileErrors(GLuint shader, const std::string &type) const;
};
