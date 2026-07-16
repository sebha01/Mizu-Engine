#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "Config.h"
#include "../ShaderClass/ShaderClass.h"

class Camera
{
	public:
		glm::vec3 Position;
		glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

		int width;
		int height;

		float speed = 0.1f;
		float sensitivity = 100.0f;

		Camera();
		Camera(int width, int height, glm::vec3 Position);

		void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform);
		void Inputs(GLFWwindow* window);
};

#endif