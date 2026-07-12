#pragma once
#include "Config.h"
//Classes
#include "Renderer/Renderer.h"

class MizuEngineWindow
{
	private:
		//default window width and height
		//const int defaultWindowWidth = 1920;
		const int defaultWindowWidth = 1080;
		const int defaultWindowHeight = 1080;

		//window, monitor and mode variables (monitor and mode more important for down the line)
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