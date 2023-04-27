#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "texture.h"
#include "arrayObject.h"
#include "arrayBuffer.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 800;

GLfloat vertices[] = {
		//  Position              Color               Texture coordinates
		//  X      Y      Z       R     G     B       X     Y
		-0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
		-0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
		0.5f, 0.0f, -0.5f, 0.83f, 0.70f, 0.44f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.5f, 0.83f, 0.70f, 0.44f, 5.0f, 0.0f,
		0.0f, 0.75f, 0.0f, 0.92f, 0.86f, 0.76f, 2.5f, 5.0f,
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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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
	VAO.Bind();

	VertexBuffer VBO(vertices, sizeof(vertices));
	ArrayBuffer IBO(indices, sizeof(indices));
	IBO.Bind();

	VAO.LinkAttribute(VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), nullptr);
	VAO.LinkAttribute(VBO, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
	VAO.LinkAttribute(VBO, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*) (6 * sizeof(GLfloat)));

	VAO.Unbind();
	VBO.Unbind();
	IBO.Unbind();

	GLint shaderScale = glGetUniformLocation(shader.ID, "scale");

	Texture texture("../tests/textures/bricks.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	texture.textureUnit(shader, "textureSampler", 0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.12f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.Activate();

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat) SCREEN_WIDTH / (GLfloat) SCREEN_HEIGHT,
												0.1f, 100.0f);

		model = glm::rotate(model, (GLfloat) glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLocation = glGetUniformLocation(shader.ID, "model");
		GLint viewLocation = glGetUniformLocation(shader.ID, "view");
		GLint projectionLocation = glGetUniformLocation(shader.ID, "projection");

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

		glUniform1f(shaderScale, 1.0f);
		texture.Bind();

		VAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO.Destroy();
	IBO.Destroy();
	VBO.Destroy();

	texture.Destroy();
	shader.Destroy();

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}
