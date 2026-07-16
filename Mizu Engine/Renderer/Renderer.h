#pragma once
#include "Config.h"

#include "Texture/Texture.h"
#include "Renderer/Colours.h"
#include "ShaderClass/ShaderClass.h"
#include "VAO/VAO.h"
#include "VBO/VBO.h"
#include "EBO/EBO.h"
#include "stb_image.h"
#include "Camera/Camera.h"

class Renderer
{
	private:
		//2D Triangle vertices
		GLfloat Triangle2DVertices[21] = {
			//	COORDINATES		//				COLOURS					//
			-0.5f, -0.5f, 0.0f,			blue.r, blue.g, blue.b, blue.a,
			 0.5f, -0.5f, 0.0f,			red.r, red.g, red.b, red.a,
			 0.0f,  0.5f, 0.0f,			yellow.r, yellow.g, yellow.b, yellow.a
		};
		//2D Indices triangle vertices
		GLfloat IndexBuffer2DTriVerts[42] = {
			//				COORDINATES				//					COLOURS						//
			-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		blue.r, blue.g, blue.b, blue.a, // Lower left corner
			 0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		green.r, green.g, green.b, green.a, // Lower right corner
			 0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,		red.r, red.g, red.b, red.a,// Upper corner
			-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,		purple.r, purple.g, purple.b, purple.a, // Inner left
			 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,		yellow.r, yellow.g, yellow.b, yellow.a,// Inner right
			 0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f ,		orange.r, orange.g, orange.b, orange.a// Inner down
		};
		//2D Triangle Indices
		GLuint IndexBufferIndices[9] = {
			0, 3, 5, //Lower left triangle
			3, 2, 4, //Lower right triangle
			5, 4, 1 //Upper triangle
		};
		//2D square vertices
		GLfloat squareVertices[36] = {
			// COORDINATES				//			COLOURS					//
			-0.5f, -0.5f, 0.0f,			green.r, green.g, green.b, green.a,	// Lower left corner
			-0.5f,  0.5f, 0.0f,			blue.r,	 blue.g,  blue.b,  blue.a,	// Lower left corner
			 0.5f,  0.5f, 0.0f,			red.r,   red.g,   red.b,   red.a,	// Lower left corner
			 0.5f, -0.5f, 0.0f,			white.r, white.g, white.b, white.a	// Lower left corner
		};
		//2D square indices   
		GLuint squareIndices[6] = {
			0, 2, 1, //Upper triangle
			0, 3, 2	//Lower triangle
		};
		//2D square vertices
		GLfloat texturedQuadVertices[36] = {
			// COORDINATES				//			COLOURS				//			TEX COORDS		//
			-0.5f, -0.5f, 0.0f,			green.r, green.g, green.b, green.a,			0.0f, 0.0f,		// Lower left corner
			-0.5f,  0.5f, 0.0f,			blue.r,	 blue.g,  blue.b,  blue.a,			0.0f, 1.0f,		// Lower left corner
			 0.5f,  0.5f, 0.0f,			red.r,   red.g,   red.b,   red.a,			1.0f, 1.0f,		// Lower left corner
			 0.5f, -0.5f, 0.0f,			white.r, white.g, white.b, white.a,			1.0f, 0.0f,		// Lower left corner
		};
		//2D square indices   
		GLuint texturedQuadIndices[6] = {
			0, 2, 1, //Upper triangle
			0, 3, 2	//Lower triangle
		};

		//Shader class object
		Shader defaultShaderProgram;
		//VAO VBO EBO
		VAO VAO1;
		VBO VBO1;
		EBO EBO1;

		//Shader filepaths
		// //2D shaders
		const char* defaultVertex2DShaderPath = "../../../Resources/Shaders/default2DShader.vert";
		const char* defaultFragment2DShaderPath = "../../../Resources/Shaders/default2DShader.frag";
		//2D texture shaders
		const char* defaultVertex2DTextureShaderPath = "../../../Resources/Shaders/default2DTextureShader.vert";
		const char* defaultFragment2DTextureShaderPath = "../../../Resources/Shaders/default2DTextureShader.frag";
		//3D shaders
		const char* defaultVertex3DShaderPath = "../../../Resources/Shaders/default3DShader.vert";
		const char* defaultFragment3DShaderPath = "../../../Resources/Shaders/default3DShader.frag";

		Texture floorTexture;
		Texture limeStoneCliffsTexture;

		//3D
		//3D pyramid vertices
		GLfloat pyramidVertices[45] =
		{ //     COORDINATES     /				COLORS					/		TexCoord  //
			-0.5f, 0.0f,  0.5f,     red.r,   red.g,   red.b,   red.a,			0.0f, 0.0f,
			-0.5f, 0.0f, -0.5f,     blue.r,  blue.g,  blue.b,  blue.a,			5.0f, 0.0f,
			 0.5f, 0.0f, -0.5f,     green.r, green.g, green.b, green.a,			0.0f, 0.0f,
			 0.5f, 0.0f,  0.5f,     white.r, white.g, white.b, white.a,			5.0f, 0.0f,
			 0.0f, 0.8f,  0.0f,     black.r, black.g, black.b, black.a,			2.5f, 5.0f
		};

		// Indices for vertices order
		GLuint pyramidIndices[18] =
		{
			0, 1, 2,
			0, 2, 3,
			0, 1, 4,
			1, 2, 4,
			2, 3, 4,
			3, 0, 4
		};

		Camera camera;
		
	public:
		//Constructor and Destructor
		Renderer();
		~Renderer();

		//General rendering functions to reduce repatition of code
		void setUpObjectsAndShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath, GLfloat verts[], GLsizeiptr vertsSize, GLuint indices[], GLsizeiptr indicesSize, bool hasEBO);
		void unbindObjects(bool hasEBO);
		void beginDrawProcess(Texture* texture);
		void deleteObjectsTexturesAndShaderProgram(Texture* texture, bool hasEBO);
		void setUpCamera(const int width, const int height);
		void enableCameraInputs(GLFWwindow* window);

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
		//Square
		void setUp2DSquare();
		void draw2DSquare();
		void delete2DSquare();
		//Textured Quad
		void setUpTexturedQuad();
		void drawTexturedQuad();
		void deleteTexturedQuad();


		//3D
		void update3DView(const int width, const int height);

		//pyramid
		void setUpPyramid();
		void drawPyramid();
		void deletePyramid();
};