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
	defaultShaderProgram = Shader("../../../Mizu Engine/Renderer/Shaders/defaultShader.vert", "../../../Mizu Engine/Renderer/Shaders/defaultShader.frag");
	//Create the VBO
	VBO1 = VBO(Triangle2DVertices, sizeof(Triangle2DVertices));
	
	//Link the VBO to the VAO
	VAO1.LinkVBO(VBO1, 0);
	//Unbind VAO
	VAO1.Unbind();
	//Unbind VBO
	VBO1.Unbind();
}

void Renderer::draw2DTriangle()
{
	//Tell OpenGL which shader program to use
	defaultShaderProgram.Activate();
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
	defaultShaderProgram = Shader("../../../Mizu Engine/Renderer/Shaders/defaultShader.vert", "../../../Mizu Engine/Renderer/Shaders/defaultShader.frag");
	//Create VBO
	VBO1 = VBO(IndexBuffer2DTriVerts, sizeof(IndexBuffer2DTriVerts));
	//Create EBO
	EBO1 = EBO(IndexBufferIndices, sizeof(IndexBufferIndices));

	//Link VBO to VAO
	VAO1.LinkVBO(VBO1, 0);
	//Unbond VAO
	VAO1.Unbind();
	//Unbind VBO
	VBO1.Unbind();
	//Unbind EBO
	EBO1.Unbind();
}

void Renderer::drawIndexBuffer2DTriangle()
{
	//Tell OpenGL which shader program to use
	defaultShaderProgram.Activate();
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
