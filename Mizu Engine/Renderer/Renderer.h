#pragma once
#include "Config.h"

#include "Renderer/Colours.h"

class Renderer
{
	private:
		//2D shapes 
		float Triangle2DVertices[9] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
		};

		GLuint VAO = 0;
		GLuint VBO = 0;
		GLuint vertexShader = 0;
		GLuint fragmentShader = 0;
		GLuint shaderProgram = 0;

		//3D shapes


public:
	//Constructor and Destructor
	Renderer();
	~Renderer();

	//2D
	void setUp2DTriangle();
	void draw2DTriangle();
	void delete2DTriangleVariables();
};