// Imports
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// Exit Codes
constexpr int SUCCESS = 0;
constexpr int ERROR = 1;
constexpr int CRITICAL_ERROR = -1;

// Screen
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 800;

// Shader Sources
const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"	 gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"	 FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\0";

int main(int argc, char** argv[])
{
	 // Set GLFW
	 glfwInit();

	 // Set Profile and Versions
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	 glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	 // Test Vertices
	 GLfloat vertices[] = {
		  -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		  0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		  0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
		  -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		  0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		  0.0f, -0.5f * float(sqrt(3)) * 2 / 6, 0.0f,
	 };

	 GLuint indices[] = {
		  0, 3, 5,
		  3, 2, 4,
		  5, 4, 1,
	 };

	 // Create Window
	 GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Graphics Test 1", NULL, NULL);

	 // Check if window cannot be created
	 if (window == NULL)
	 {
		  std::cout << "Failed to create window!" << std::endl;
		  glfwTerminate();
		  return CRITICAL_ERROR;
	 }

	 // Introduce the window into the current context and load graphics
	 glfwMakeContextCurrent(window);
	 gladLoadGL();

	 // Set Graphics Viewport from x = 0, y = 0 to the screen width and screen height
	 glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	 // Store Vertex Shader
	 GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	 glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	 glCompileShader(vertexShader);

	 // Store Fragment Shader
	 GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	 glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	 glCompileShader(fragmentShader);

	 // Create Shader Program and attach shaders
	 GLuint shaderProgram = glCreateProgram();
	 glAttachShader(shaderProgram, vertexShader);
	 glAttachShader(shaderProgram, fragmentShader);

	 // Link shader program
	 glLinkProgram(shaderProgram);

	 // Delete old shaders
	 glDeleteShader(vertexShader);
	 glDeleteShader(fragmentShader);

	 // Create objects
	 GLuint arrayObject, bufferObject, indiceObject;

	 // Set Buffers
	 glGenVertexArrays(1, &arrayObject);
	 glGenBuffers(1, &bufferObject);
	 glGenBuffers(1, &indiceObject);
	 glBindVertexArray(arrayObject);

	 // Bind Buffers
	 glBindBuffer(GL_ARRAY_BUFFER, bufferObject);
	 glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceObject);
	 glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	 // Set Vertex Attributes
	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	 glEnableVertexAttribArray(0);

	 // Bind Vertex Attributes
	 glBindBuffer(GL_ARRAY_BUFFER, 0);
	 glBindVertexArray(0);
	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	 // Remove Default Color and set a new color
	 glClearColor(0.18f, 0.65f, 0.2f, 1.0f);
	 glClear(GL_COLOR_BUFFER_BIT);
	 glfwSwapBuffers(window);

	 // Mainloop
	 while (!glfwWindowShouldClose(window))
	 {
		  // Set Window Attributes
		  glClearColor(0.18f, 0.65f, 0.2f, 1.0f);
		  glClear(GL_COLOR_BUFFER_BIT);
		  glUseProgram(shaderProgram);
		  glBindVertexArray(arrayObject);
		  glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		  glfwSwapBuffers(window);

		  // Process the current Events
		  glfwPollEvents();
	 }

	 // Successfully Terminate Session
	 glDeleteVertexArrays(1, &arrayObject);
	 glDeleteBuffers(1, &bufferObject);
	 glDeleteBuffers(1, &indiceObject);
	 glDeleteProgram(shaderProgram);

	 glfwDestroyWindow(window);
	 glfwTerminate();

	 return SUCCESS;
}