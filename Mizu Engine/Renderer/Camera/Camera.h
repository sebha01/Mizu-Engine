#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "Config.h"
#include "../ShaderClass/ShaderClass.h"

class Camera
{
	public:
		//Stores main vectors of the camera
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::mat4 cameraMatrix = glm::mat4(1.0f);

		//Prevents camera jumping around when first clicking window
		bool firstClick = true;

		//Width and height of window
		int width;
		int height;

		//Speed of camera and it's sensitivity
		float speed = 0.01f;
		float sensitivity = 100.0f;

		//Default constructor
		Camera();
		//Constructor to set up initial values
		Camera(int width, int height, glm::vec3 Position);

		//Updates and exports camera matrix to the vertex shader
		void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
		void Matrix(Shader& shader, const char* uniform);
		//Handles camera inputs
		void Inputs(GLFWwindow* window);
};

#endif