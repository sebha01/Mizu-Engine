#include "MizuEngineWindow.h"

//CALLBACK FUNCTIONS
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//Window Input functions
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//WINDOW CLASS FUNCTIONS

MizuEngineWindow::MizuEngineWindow()
{
}

MizuEngineWindow::~MizuEngineWindow()
{
}

void MizuEngineWindow::WindowInit()
{
	if (!glfwInit())
	{
		return;
	}

	//Set openGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Include for mac os
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//Create window and set context
	
	//initalise window mode and monitor
	//monitor = glfwGetPrimaryMonitor();
	//mode = glfwGetVideoMode(monitor);

	//window = glfwCreateWindow(mode->width * 0.66, mode->height * 0.66, "Mizu Engine v1.0.0", NULL, NULL);
	window = glfwCreateWindow(defaultWindowWidth, defaultWindowHeight, "Mizu Engine v1.0.0", NULL, NULL);

	//Register callback function 
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//set window as the current context
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Couldn't load opengl, failed to initialise GLAD." << std::endl;
		glfwTerminate();
		return;
	}

	//Set screen colour
	glClearColor(0.08f, 0.12f, 0.35f, 1.0f);

	//Set viewport
	//glViewport(0, 0, mode->width * 0.66, mode->height * 0.66);
	glViewport(0, 0, defaultWindowWidth, defaultWindowHeight);

	MizuEngineRenderer.setUp2DTriangle();
}

void MizuEngineWindow::WindowUpdate()
{
	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//Clear colour from last frame
		glClearColor(0.08f, 0.12f, 0.35f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//rendering loop here
		MizuEngineRenderer.draw2DTriangle();

		//check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void MizuEngineWindow::WindowTerminate()
{
	MizuEngineRenderer.delete2DTriangleVariables();

	glfwTerminate();
}
