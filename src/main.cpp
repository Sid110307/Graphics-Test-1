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
		// Bottom
		-0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 5.0f, 0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 5.0f, 0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f,

		// Left
		-0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, -0.75f, -0.5f, 0.0f,
		-0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, -0.75f, -0.5f, 0.0f,
		0.0f, 0.75f, 0.0f, 0.92, 0.86, 0.76, 2.5f, 5.0f, -0.75f, -0.5f, 0.0f,

		// Back
		-0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, 0.0f, -0.5f, -0.75f,
		0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.0f, -0.5f, -0.75f,
		0.0f, 0.75f, 0.0f, 0.92, 0.86, 0.76, 2.5f, 5.0f, 0.0f, -0.5f, -0.75f,

		// Right
		0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.75f, 0.5f, 0.0f,
		0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, 0.75f, 0.5f, 0.0f,
		0.0f, 0.75f, 0.0f, 0.92, 0.86, 0.76, 2.5f, 5.0f, 0.75f, 0.5f, 0.0f,

		// Front
		0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f, 0.0f, 0.5f, 0.75f,
		-0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f, 0.0f, 0.5f, 0.75f,
		0.0f, 0.75f, 0.0f, 0.92, 0.86, 0.76, 2.5f, 5.0f, 0.0f, 0.5f, 0.75f,
};

GLuint indices[] = {
		0, 1, 2, // Bottom
		0, 2, 3, // Bottom
		4, 6, 5, // Left
		7, 9, 8, // Back
		10, 12, 11, // Right
		13, 15, 14 // Front
};

GLfloat lightVertices[] = {
		-0.1f, -0.1f, 0.1f,
		-0.1f, -0.1f, -0.1f,
		0.1f, -0.1f, -0.1f,
		0.1f, -0.1f, 0.1f,
		-0.1f, 0.1f, 0.1f,
		-0.1f, 0.1f, -0.1f,
		0.1f, 0.1f, -0.1f,
		0.1f, 0.1f, 0.1f
};

GLuint lightIndices[] = {
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
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
	Shader shader("../lib/shaders/modelVertex.glsl", "../lib/shaders/modelFragment.glsl");

	ArrayObject VAO;
	VAO.bind();

	VertexBuffer VBO(vertices, sizeof(vertices));
	ArrayBuffer IBO(indices, sizeof(indices));
	IBO.bind();

	VAO.linkAttribute(VBO, 0, 3, GL_FLOAT, 11 * sizeof(GLfloat), nullptr);
	VAO.linkAttribute(VBO, 1, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
	VAO.linkAttribute(VBO, 2, 2, GL_FLOAT, 11 * sizeof(GLfloat), (void*) (6 * sizeof(GLfloat)));
	VAO.linkAttribute(VBO, 3, 3, GL_FLOAT, 11 * sizeof(GLfloat), (void*) (8 * sizeof(GLfloat)));

	VAO.unbind();
	VBO.unbind();
	IBO.unbind();

	Shader lightShader("../lib/shaders/lightVertex.glsl", "../lib/shaders/lightFragment.glsl");
	ArrayObject lightVAO;
	lightVAO.bind();

	VertexBuffer lightVBO(lightVertices, sizeof(lightVertices));
	ArrayBuffer lightIBO(lightIndices, sizeof(lightIndices));
	lightVAO.linkAttribute(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), nullptr);

	lightVAO.unbind();
	lightVBO.unbind();
	lightIBO.unbind();

	glm::vec3 lightPos(0.5f, 0.5f, 0.5f);
	glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
	glm::mat4 lightModel = glm::translate(glm::mat4(1.0f), lightPos);

	glm::vec3 objectPos(0.0f, 0.0f, 0.0f);
	glm::mat4 objectModel = glm::translate(glm::mat4(1.0f), objectPos);

	lightShader.activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.id, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.id, "lightColor"), lightColor.x, lightColor.y, lightColor.z,
				lightColor.w);

	shader.activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.id, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shader.id, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shader.id, "lightPosition"), lightPos.x, lightPos.y, lightPos.z);

	Texture texture("../lib/textures/bricks.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	texture.textureUnit(shader, "textureSampler", 0);

	glEnable(GL_DEPTH_TEST);
	glm::vec3 cameraPosition(0.0f, 0.0f, 2.0f);
	Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, cameraPosition);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.12f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.keyboard(window);
		camera.setMatrix(45.0f, 0.1f, 100.0f);

		shader.activate();
		glUniform3f(glGetUniformLocation(shader.id, "cameraPosition"), cameraPosition.x, cameraPosition.y,
					cameraPosition.z);
		camera.createMatrix(shader, "camMatrix");
		texture.bind();

		VAO.bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);

		lightShader.activate();
		camera.createMatrix(lightShader, "camMatrix");
		lightVAO.bind();
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO.destroy();
	IBO.destroy();
	VBO.destroy();
	lightVAO.destroy();
	lightIBO.destroy();
	lightVBO.destroy();

	texture.destroy();
	shader.destroy();
	lightShader.destroy();

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}
