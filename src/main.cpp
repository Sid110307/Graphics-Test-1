#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "./shader.h"
#include "./arrayObject.h"
#include "./arrayBuffer.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 800;

GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.6f, 0.32f,
		-0.25f, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.9f, 0.45f, 0.17f,
		0.25f, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.9f, 0.45f, 0.17f,
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f,
};

GLuint indices[] = {
		0, 3, 5,
		3, 2, 4,
		5, 4, 1,
};

//GLfloat vertices[] = {
//		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
//		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
//		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
//		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
//};

//GLuint indices[] = {
//		0, 2, 1,
//		0, 3, 2,
//};

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
										  "Graphics Test 1", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cerr << "Error: Failed to create window (" << std::strerror(errno)
				  << ")" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Shader shader;

	ArrayObject VAO;
	VAO.Bind();

	VertexBuffer VBO(vertices, sizeof(vertices));
	ArrayBuffer IBO(indices, sizeof(indices));
	IBO.Bind();

	VAO.LinkAttribute(VBO, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), nullptr);
	VAO.LinkAttribute(VBO, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat),
					  (void*) (3 * sizeof(GLfloat)));

	VAO.Unbind();
	VBO.Unbind();
	IBO.Unbind();

	GLint uniformID = glGetUniformLocation(shader.ID, "scale");

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.12f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Activate();
		glUniform1f(uniformID, 0.75f);
		VAO.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint),
					   GL_UNSIGNED_INT, nullptr);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO.Destroy();
	IBO.Destroy();
	VBO.Destroy();
	shader.Destroy();

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}
