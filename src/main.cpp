#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "include/shader.h"
#include "include/texture.h"
#include "include/arrayObject.h"
#include "include/arrayBuffer.h"
#include "include/camera.h"

GLfloat vertices[] = {
		//  Position              Color               Texture coordinates
		//  X      Y      Z       R     G     B       X     Y
		-0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 2.5f, 0.0f,
		0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 2.5f, 0.0f,
		0.0f, 0.75f, 0.0f, 0.92f, 0.86f, 0.76f, 1.25f, 2.5f,
};

GLuint indices[] = {
		0, 1, 2,
		0, 2, 3,
		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4,
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
										  "Graphics Test 1", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cerr << "Error: Failed to create window (" << std::strerror(errno) << ")" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Shader shader;

	ArrayObject VAO;
	VAO.bind();

	VertexBuffer VBO(vertices, sizeof(vertices));
	ArrayBuffer IBO(indices, sizeof(indices));
	IBO.bind();

	VAO.linkAttribute(VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), nullptr);
	VAO.linkAttribute(VBO, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
	VAO.linkAttribute(VBO, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*) (6 * sizeof(GLfloat)));

	VAO.unbind();
	VBO.unbind();
	IBO.unbind();

	Texture texture("../tests/textures/bricks.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	texture.textureUnit(shader, "textureSampler", 0);

	glEnable(GL_DEPTH_TEST);
	Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.12f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.activate();

		camera.matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");
		camera.keyboard(window);

		texture.bind();

		VAO.bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO.destroy();
	IBO.destroy();
	VBO.destroy();

	texture.destroy();
	shader.destroy();

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}
