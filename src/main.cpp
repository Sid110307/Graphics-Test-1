#include <iostream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shader.h"
#include "texture.h"
#include "arrayObject.h"
#include "arrayBuffer.h"

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 800;

GLfloat vertices[] = {
//  Position              Color               Texture coordinates
//  X      Y      Z       R     G     B       X     Y
	-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
	-0.5f, 0.5f,  0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
	0.5f,  0.5f,  0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f,
	0.5f,  -0.5f, 0.0f,   0.0f, 0.0f, 0.5f,   1.0f, 0.0f,
};

GLuint indices[] = {
	0, 1, 2,
	2, 3, 0,
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

	VAO.LinkAttribute(VBO, 0, 3, GL_FLOAT, 8 * sizeof(GLfloat), nullptr);
	VAO.LinkAttribute(VBO, 1, 3, GL_FLOAT, 8 * sizeof(GLfloat),
					  (void*) (3 * sizeof(GLfloat)));
	VAO.LinkAttribute(VBO, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat),
					  (void*) (6 * sizeof(GLfloat)));

	VAO.Unbind();
	VBO.Unbind();
	IBO.Unbind();

	GLint shaderScale = glGetUniformLocation(shader.ID, "scale");

	std::string cwd = std::filesystem::current_path().string();
	cwd = cwd.substr(0, cwd.find("bin") - 1);
	cwd += "/tests/textures/1920x1080.jpg";
	
	std::cout << cwd << std::endl;

	Texture texture(cwd.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	texture.textureUnit(shader, "textureSampler", 0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.12f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		shader.Activate();

		glUniform1f(shaderScale, 0.5f);
		texture.Bind();

		VAO.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint),
					   GL_UNSIGNED_INT, nullptr);

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
