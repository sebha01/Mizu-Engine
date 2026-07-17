#include "MizuEngineWindow.h"

//CALLBACK FUNCTIONS
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//Resize the viewport appropriately depending on if the user minimises or maximises the window
	glViewport(0, 0, width, height);
}

//Window Input functions
void processInput(GLFWwindow* window)
{
	//If escape button pressed close the window
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
	//Initialise glfw
	if (!glfwInit())
	{
		return;
	}

	//Let glfw know the version of OpenGL being used
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//Tell glfw the core version of OpenGL is being used so we only have the modern functions
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


	//Load OpenGL and initialise GLAD
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

	MizuEngineRenderer.setUpCamera(defaultWindowWidth, defaultWindowHeight);

	//Set up everything needed to render the 2D Triangle
	//MizuEngineRenderer.setUp2DTriangle();
	//MizuEngineRenderer.setUpIndexBuffer2DTriangle();
	//MizuEngineRenderer.setUp2DSquare();
	//MizuEngineRenderer.setUpTexturedQuad();
	//MizuEngineRenderer.setUpPyramid();
	MizuEngineRenderer.setUpLitPyramid();
}

void MizuEngineWindow::WindowUpdate()
{
	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//process keyboard input while interacting with the window
		processInput(window);

		//Clear colour from last frame and specify bg colour
		glClearColor(0.08f, 0.12f, 0.35f, 1.0f);
		//Clear back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//rendering loop here
		//Handles camera inputs within the scene
		MizuEngineRenderer.enableCameraInputs(window);
		//Update the 3D view of the scene
		MizuEngineRenderer.update3DView(defaultWindowWidth, defaultWindowHeight);
		
		//MizuEngineRenderer.draw2DTriangle();
		//MizuEngineRenderer.drawIndexBuffer2DTriangle();
		//MizuEngineRenderer.draw2DSquare();
		//MizuEngineRenderer.drawTexturedQuad();
		//MizuEngineRenderer.drawPyramid();
		MizuEngineRenderer.drawLitPyramid();

		//swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		//Take care of all GLFW events
		glfwPollEvents();
	}
}

void MizuEngineWindow::WindowTerminate()
{
	//Delete all objects created when rendering 2d Triangle
	//MizuEngineRenderer.delete2DTriangleVariables();
	//MizuEngineRenderer.deleteIndexBuffer2DTriangleVariables();
	//MizuEngineRenderer.delete2DSquare();
	//MizuEngineRenderer.deleteTexturedQuad();
	//MizuEngineRenderer.deletePyramid();
	MizuEngineRenderer.deleteLitPyramid();

	//Terminate GLFW before ending the program
	glfwTerminate();
}
