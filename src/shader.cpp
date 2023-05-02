#include "include/shader.h"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	const GLchar* vertexSource = readShader(vertexPath);
	const GLchar* fragmentSource = readShader(fragmentPath);

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, nullptr);
	glCompileShader(vertexShader);
	checkCompileErrors(vertexShader, "VERTEX");

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
	glCompileShader(fragmentShader);
	checkCompileErrors(fragmentShader, "FRAGMENT");

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);

	glLinkProgram(id);
	checkCompileErrors(id, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::activate() const
{
	glUseProgram(id);
}

void Shader::destroy() const
{
	glDeleteProgram(id);
}

void Shader::checkCompileErrors(GLuint shader, const std::string &type)
{
	GLint success;
	GLchar infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "Error: Shader compilation failed (" << infoLog << ")" << std::endl;
		}
	} else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
			std::cerr << "Error: Shader program linking failed (" << infoLog << ")" << std::endl;
		}
	}
}

const GLchar* Shader::readShader(const GLchar* path)
{
	std::ifstream file;
	std::stringstream stream;

	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(path);
		stream << file.rdbuf();
		file.close();
	}
	catch (std::ifstream::failure &e)
	{
		std::cerr << "Error: Shader file could not be read (" << path << ")" << std::endl;
	}

	const GLchar* shaderSource = new GLchar[stream.str().length() + 1];
	std::strcpy(const_cast<GLchar*>(shaderSource), stream.str().c_str());

	return shaderSource;
}
