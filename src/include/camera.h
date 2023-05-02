#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shader.h"

class Camera
{
public:
	Camera(GLint, GLint, glm::vec3);

	void setMatrix(GLfloat, GLfloat, GLfloat);
	void createMatrix(Shader &, const char*);
	void keyboard(GLFWwindow*);

private:
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 originalPosition = position, originalOrientation = orientation, originalUp = up;

	glm::mat4 cameraMatrix;
	GLint width, height;
	GLfloat speed = 0.025f;
	GLfloat sensitivity = 100.0f;

	bool firstMouse = true;
};
