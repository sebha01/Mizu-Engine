#pragma once
#include "Config.h"

#include "Renderer/Colours.h"
#include "ShaderClass/ShaderClass.h"
#include "VAO/VAO.h"
#include "VBO/VBO.h"
#include "EBO/EBO.h"

class Renderer
{
	private:
		//2D Triangle vertices
		GLfloat Triangle2DVertices[21] = {
		-0.5f, -0.5f, 0.0f, blue.r, blue.g, blue.b, blue.a,
		 0.5f, -0.5f, 0.0f, red.r, red.g, red.b, red.a,
		 0.0f,  0.5f, 0.0f, yellow.r, yellow.g, yellow.b, yellow.a
		};
		//2D Indices triangle vertices
		GLfloat IndexBuffer2DTriVerts[42] = {
			-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, blue.r, blue.g, blue.b, blue.a, // Lower left corner
			0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, green.r, green.g, green.b, green.a, // Lower right corner
			0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, red.r, red.g, red.b, red.a,// Upper corner
			-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, purple.r, purple.g, purple.b, purple.a, // Inner left
			0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, yellow.r, yellow.g, yellow.b, yellow.a,// Inner right
			0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f , orange.r, orange.g, orange.b, orange.a// Inner down
		};
		//2D Triangle Indices
		GLuint IndexBufferIndices[9] = {
			0, 3, 5, //Lower left triangle
			3, 2, 4, //Lower right triangle
			5, 4, 1 //Upper triangle
		};

		//Shader class object
		Shader defaultShaderProgram;
		//VAO VBO EBO
		VAO VAO1;
		VBO VBO1;
		EBO EBO1;

	public:
		//Constructor and Destructor
		Renderer();
		~Renderer();

		//2D

		//Triangle
		//Normal triangle
		void setUp2DTriangle();
		void draw2DTriangle();
		void delete2DTriangleVariables();
		//Indices triangle
		void setUpIndexBuffer2DTriangle();
		void drawIndexBuffer2DTriangle();
		void deleteIndexBuffer2DTriangleVariables();
};