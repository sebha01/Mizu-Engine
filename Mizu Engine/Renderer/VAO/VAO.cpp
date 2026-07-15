#include "VAO.h"

VAO::VAO()
{
}

void VAO::Create()
{
	//Generate VAO object
	glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	//Bind the VBO
	VBO.Bind();
	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);

	//Enable the vertex attribute so that OpenGL
	glEnableVertexAttribArray(layout);
	//Unbind the VBO
	VBO.Unbind();
}

void VAO::Bind()
{
	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(ID);
}

void VAO::Unbind()
{
	// Bind both the VAO to 0 so that we don't accidentally modify the VAO
	glBindVertexArray(0);
}

void VAO::Delete()
{
	//Delete VAO object
	glDeleteVertexArrays(1, &ID);
}