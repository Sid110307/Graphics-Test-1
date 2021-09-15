#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define SUCCESS 0;
#define ERROR 1;
#define CRITICAL_ERROR -1;

int main(int argc, char** argv[])
{

	 glfwInit();

	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	 glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	 GLFWwindow* window = glfwCreateWindow(800, 600, "Graphics Test 1", NULL, NULL);

	 if (window == NULL)
	 {
		  std::cout << "Failed to create window!" << std::endl;
		  glfwTerminate();
		  return CRITICAL_ERROR;
	 }

	 glfwMakeContextCurrent(window);

	 // Start Graphics

	 glfwDestroyWindow(window);
	 glfwTerminate();
	 return SUCCESS;
}