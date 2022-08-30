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

		out vec3 outputColor;
		uniform float scale;

		void main() {
			gl_Position = vec4(position.x * scale, position.y * scale, position.z * scale, 1.0f);
			outputColor = color;
		}
	)glsl";

	const char* fragmentSource = R"glsl(
		#version 330 core

		in vec3 outputColor;
		out vec4 fragmentColor;

		void main() {
			fragmentColor = vec4(outputColor, 1.0);
		}
	)glsl";

	void CheckCompileErrors(GLuint shader, const std::string& type) const;
};
