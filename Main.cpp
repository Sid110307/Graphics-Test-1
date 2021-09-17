#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "shader.h"
#include "ArrayObject.h"
#include "ArrayBuffer.h"
#include "VertexBuffer.h"

constexpr int SUCCESS = 0;
constexpr int ERROR = 1;
constexpr int CRITICAL_ERROR = -1;

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 800;

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

/// <summary>
/// Main Graphics Class
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char** argv[])
{
	 glfwInit();

	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	 glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	 GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Graphics Test 1", NULL, NULL);

	 if (window == NULL)
	 {
		  std::cout << "Failed to create window!" << std::endl;
		  glfwTerminate();
		  return CRITICAL_ERROR;
	 }

	 glfwMakeContextCurrent(window);
	 gladLoadGL();

	 glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	 Shader shaderProgram("default.vert", "default.frag");

	 ArrayObject arrayObject1;
	 arrayObject1.Bind();

	 VertexBuffer vertexBuffer1(vertices, sizeof(vertices));
	 ArrayBuffer arrayBuffer1(indices, sizeof(indices));

	 arrayObject1.LinkObject(vertexBuffer1, 0);
	 arrayObject1.Unbind();

	 vertexBuffer1.Unbind();
	 arrayBuffer1.Unbind();

	 while (!glfwWindowShouldClose(window))
	 {
		  glClearColor(0.18f, 0.75f, 0.2f, 1.0f);
		  glClear(GL_COLOR_BUFFER_BIT);

		  shaderProgram.Activate();
		  arrayObject1.Bind();

		  glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		  glfwSwapBuffers(window);
		  glfwPollEvents();
	 }

	 arrayObject1.Destroy();
	 arrayBuffer1.Destroy();
	 vertexBuffer1.Destroy();
	 shaderProgram.Destroy();

	 glfwDestroyWindow(window);
	 glfwTerminate();

	 return SUCCESS;
}