#include "include/mesh.h"

Vertex vertices[] = {
		Vertex{glm::vec3(-1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			   glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			   glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			   glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			   glm::vec2(1.0f, 0.0f)}
};

GLuint indices[] = {
		0, 1, 2,
		0, 2, 3
};

Vertex lightVertices[] = {
		Vertex{glm::vec3(-0.1f, -0.1f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			   glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			   glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.1f, -0.1f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			   glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.1f, -0.1f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			   glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			   glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			   glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.1f, 0.1f, -0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			   glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f),
			   glm::vec2(0.0f, 0.0f)}
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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Graphics Test 1", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "Error: Failed to create window (" << std::strerror(errno) << ")" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Texture textures[] = {
			Texture("../lib/textures/bricks.png", "diffuse", GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE),
			Texture("../lib/textures/bricks_specular.png", "specular", GL_TEXTURE1, GL_RED, GL_UNSIGNED_BYTE)
	};

	Shader shader("../lib/shaders/modelVertex.glsl", "../lib/shaders/modelFragment.glsl");
	std::vector<Vertex> verticesVector(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<GLuint> indicesVector(indices, indices + sizeof(indices) / sizeof(GLuint));
	std::vector<Texture> texturesVector(textures, textures + sizeof(textures) / sizeof(Texture));
	Mesh floor(verticesVector, indicesVector, texturesVector);

	Shader lightShader("../lib/shaders/lightVertex.glsl", "../lib/shaders/lightFragment.glsl");
	std::vector<Vertex> lightVerticesVector(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<GLuint> lightIndicesVector(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	Mesh light(lightVerticesVector, lightIndicesVector, texturesVector);

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

	glEnable(GL_DEPTH_TEST);
	glm::vec3 cameraPosition(0.0f, 2.0f, 2.0f);
	Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, cameraPosition);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.12f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.keyboard(window);
		camera.setMatrix(45.0f, 0.1f, 100.0f);

		floor.draw(shader, camera);
		light.draw(lightShader, camera);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shader.destroy();
	lightShader.destroy();

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}
