// Mizu Engine.cpp : Defines the entry point for the application.
//

#include "Config.h"

int main()
{
	GLFWwindow* window;

	if (!glfwInit())
	{
		return -1;
	}

	//Set openGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create window and set context
	window = glfwCreateWindow(640, 480, "Mizu Engine v1.0", NULL, NULL);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Couldn't load opengl" << std::endl;
		glfwTerminate();
		return -1;
	}

	glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		glSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
