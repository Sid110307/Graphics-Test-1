#include "include/camera.h"

Camera::Camera(GLint width, GLint height, glm::vec3 position)
{
	this->width = width;
	this->height = height;
	this->position = position;

	originalPosition = position;
	originalOrientation = orientation;
	originalUp = up;
}

void Camera::matrix(GLfloat fov, GLfloat nearPlane, GLfloat farPlane, Shader &shader, const char* uniform) const
{
	glm::mat4 view = glm::lookAt(position, position + orientation, up);
	glm::mat4 projection = glm::perspective(glm::radians(fov), (GLfloat) width / (GLfloat) height, nearPlane, farPlane);

	glUniformMatrix4fv(glGetUniformLocation(shader.id, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::keyboard(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) position += speed * up;
		else position += speed * orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) position -= speed * up;
		else position -= speed * orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= glm::normalize(glm::cross(orientation, up)) * speed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += glm::normalize(glm::cross(orientation, up)) * speed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position = originalPosition;
		orientation = originalOrientation;
		up = originalUp;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		if (firstMouse)
		{
			glfwSetCursorPos(window, (GLfloat) width / 2, (GLfloat) height / 2);
			firstMouse = false;
		}

		GLdouble mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		GLfloat rotationX = sensitivity * (GLfloat) (mouseY - (GLfloat) height / 2) / (GLfloat) height;
		GLfloat rotationY = sensitivity * (GLfloat) (mouseX - (GLfloat) width / 2) / (GLfloat) width;

		glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotationX),
											   glm::normalize(glm::cross(orientation, up)));

		if (!(glm::angle(newOrientation, up) <= glm::radians(5.0f) ||
			  glm::angle(newOrientation, -up) <= glm::radians(5.0f)))
			orientation = newOrientation;

		orientation = glm::rotate(orientation, glm::radians(-rotationY), up);
		glfwSetCursorPos(window, (GLfloat) width / 2, (GLfloat) height / 2);
	} else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstMouse = true;
	}
}
