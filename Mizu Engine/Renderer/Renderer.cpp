#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::setUp2DTriangle()
{
	//Create VAO
	VAO1.Create();
	//Bind the VAO
	VAO1.Bind();

	//Create the shader program
	defaultShaderProgram = Shader(vertexShaderPath, fragmentShaderPath);
	//Create the VBO
	VBO1 = VBO(Triangle2DVertices, sizeof(Triangle2DVertices));
	
	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	//Unbind VAO
	VAO1.Unbind();
	//Unbind VBO
	VBO1.Unbind();
}

void Renderer::draw2DTriangle()
{
	//Gets ID of uniform called scale
	uniID = glGetUniformLocation(defaultShaderProgram.ID, "scale");
	//Tell OpenGL which shader program to use
	defaultShaderProgram.Activate();
	//Assigns value to the uniform
	//NOTE: Must always be done after activating the shader program
	glUniform1f(uniID, 0.5f);
	//Bind VAO so OpenGL knows to use it 
	VAO1.Bind();
	//Draw the triangle using GL_TRIANGLES primitive
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::delete2DTriangleVariables()
{
	//Delete all objects created when rendering the 2D triangle
	VAO1.Delete();
	VBO1.Delete();
	defaultShaderProgram.Delete();
}

void Renderer::setUpIndexBuffer2DTriangle()
{
	//Create VAO
	VAO1.Create();
	//Bind the VAO
	VAO1.Bind();

	//Create shader program
	defaultShaderProgram = Shader(vertexShaderPath, fragmentShaderPath);
	//Create VBO
	VBO1 = VBO(IndexBuffer2DTriVerts, sizeof(IndexBuffer2DTriVerts));
	//Create EBO
	EBO1 = EBO(IndexBufferIndices, sizeof(IndexBufferIndices));

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	//Unbond VAO
	VAO1.Unbind();
	//Unbind VBO
	VBO1.Unbind();
	//Unbind EBO
	EBO1.Unbind();
}

void Renderer::drawIndexBuffer2DTriangle()
{
	//Gets ID of uniform called scale
	uniID = glGetUniformLocation(defaultShaderProgram.ID, "scale");
	//Tell OpenGL which shader program to use
	defaultShaderProgram.Activate();
	//Assigns value to the uniform
	//NOTE: Must always be done after activating the shader program
	glUniform1f(uniID, 0.5f);
	//Bind VAO so OpenGL knows to use it 
	VAO1.Bind();
	//Draw the triangle using GL_TRIANGLES primitive
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}

void Renderer::deleteIndexBuffer2DTriangleVariables()
{
	//Delete all objects created when rendering the 2D Indices triangle
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
}

void Renderer::setUp2DSquare()
{
	//Create VAO
	VAO1.Create();
	//Bind the VAO
	VAO1.Bind();

	//Create shader program
	defaultShaderProgram = Shader(vertexShaderPath, fragmentShaderPath);
	//Create VBO
	VBO1 = VBO(squareVertices, sizeof(squareVertices));
	//Create EBO
	EBO1 = EBO(squareIndices, sizeof(squareIndices));

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	//Unbond VAO
	VAO1.Unbind();
	//Unbind VBO
	VBO1.Unbind();
	//Unbind EBO
	EBO1.Unbind();
}

void Renderer::draw2DSquare()
{
	//Gets ID of uniform called scale
	uniID = glGetUniformLocation(defaultShaderProgram.ID, "scale");
	//Tell OpenGL which shader program to use
	defaultShaderProgram.Activate();
	//Assigns value to the uniform
	//NOTE: Must always be done after activating the shader program
	glUniform1f(uniID, 0.5f);
	//Bind VAO so OpenGL knows to use it 
	VAO1.Bind();
	//Draw the triangle using GL_TRIANGLES primitive
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::delete2DSquare()
{
	//Delete all objects created when rendering the 2D Indices triangle
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
}

void Renderer::setUpTexturedQuad()
{
	//Create VAO
	VAO1.Create();
	//Bind the VAO
	VAO1.Bind();

	//Create shader program
	defaultShaderProgram = Shader(vertexShaderPath, fragmentShaderPath);
	//Create VBO
	VBO1 = VBO(squareVertices, sizeof(squareVertices));
	//Create EBO
	EBO1 = EBO(squareIndices, sizeof(squareIndices));

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 9 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(GLfloat), (void*)(7 * sizeof(float)));
	//Unbond VAO
	VAO1.Unbind();
	//Unbind VBO
	VBO1.Unbind();
	//Unbind EBO
	EBO1.Unbind();

	floorTexture = Texture("../../../Resources/Textures/AngledBlocksFloor/angled-blocks-vegetation_albedo.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	floorTexture.texUnit(defaultShaderProgram, "tex0", 0);
}

void Renderer::drawTexturedQuad()
{
	//Gets ID of uniform called scale
	uniID = glGetUniformLocation(defaultShaderProgram.ID, "scale");
	
	//Assigns value to the uniform
	//NOTE: Must always be done after activating the shader program
	glUniform1f(uniID, 0.5f);
	floorTexture.Bind();
	//Bind VAO so OpenGL knows to use it 
	VAO1.Bind();
	//Draw the triangle using GL_TRIANGLES primitive
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::deleteTexturedQuad()
{
	//Delete all objects created when rendering the 2D Indices triangle
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	floorTexture.Delete();
}