#include "shader.h"

std::string readFileContents(const char* filename)
{
	 std::ifstream input(filename, std::ios::binary);

	 if (input)
	 {
		  std::string contents;
		  input.seekg(0, std::ios::end);
		  contents.resize(input.tellg());
		  input.seekg(0, std::ios::beg);
		  input.read(&contents[0], contents.size());
		  input.close();
		  return contents;
	 }

	 throw errno;
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	 std::string vertexCode = readFileContents(vertexFile);
	 std::string fragmentCode = readFileContents(fragmentFile);

	 const char* vertexSource = vertexCode.c_str();
	 const char* fragmentSource = fragmentCode.c_str();

	 GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	 glShaderSource(vertexShader, 1, &vertexSource, NULL);
	 glCompileShader(vertexShader);

	 GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	 glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	 glCompileShader(fragmentShader);

	 ID = glCreateProgram();
	 glAttachShader(ID, vertexShader);
	 glAttachShader(ID, fragmentShader);

	 glLinkProgram(ID);

	 glDeleteShader(vertexShader);
	 glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	 glUseProgram(ID);
}

void Shader::Destroy()
{
	 glDeleteProgram(ID);
}