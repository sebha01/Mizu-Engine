#pragma once
#include "Config.h"
//Classes
#include "Renderer/Renderer.h"

class MizuEngineWindow
{
	private:
		//width and height
		const int defaultWindowWidth = 1920;
		const int defaultWindowHeight = 1080;

		//window, monitor and mode variables
		GLFWwindow* window;
		GLFWmonitor* monitor;
		const GLFWvidmode* mode;

		//Renderer
		Renderer MizuEngineRenderer;
	public:
		//Constructor 
		MizuEngineWindow();
		~MizuEngineWindow();

		//Member functions 
		//Initialising and terminating the window
		void WindowInit();
		void WindowUpdate();
		void WindowTerminate();
};