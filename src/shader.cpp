#include "shader.h"

Shader::Shader()
{
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);
	CheckCompileErrors(vertexShader, "VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);
	CheckCompileErrors(fragmentShader, "FRAGMENT");

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);
	CheckCompileErrors(ID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate() const
{
	glUseProgram(ID);
}

void Shader::Destroy() const
{
	glDeleteProgram(ID);
}

void Shader::CheckCompileErrors(GLuint shader, const std::string &type) const
{
	GLint success;
	GLchar infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "Error: Shader compilation failed (" << infoLog << ")"
					  << std::endl;
		}
	} else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "Error: Shader program linking failed (" << infoLog
					  << ")" << std::endl;
		}
	}
}
