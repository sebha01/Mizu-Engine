#pragma once
#include "Config.h"

#include "Renderer/Colours.h"

class Renderer
{
	private:
		//2D Triangle vertices
		float Triangle2DVertices[9] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
		};

		float IndexBuffer2DTriVerts[18] = {
			-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
			0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
			0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
			-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
			0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
			0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
		};
		GLuint IndexBufferIndices[9] = {		
			0, 3, 5, //Lower left triangle
			3, 2, 4, //Lower right triangle
			5, 4, 1 //Upper triangle
		};

		//Reference containers for the vertex buffer object and vertex array object
		GLuint VAO = 0;
		GLuint VBO = 0;
		GLuint EBO = 0;

public:
	//Constructor and Destructor
	Renderer();
	~Renderer();

	//2D

	//Triangle
	void setUp2DTriangle();
	void draw2DTriangle();
	void delete2DTriangleVariables();

	void setUpIndexBuffer2DTriangle();
	void drawIndexBuffer2DTriangle();
	void deleteIndexBuffer2DTriangleVariables();
};