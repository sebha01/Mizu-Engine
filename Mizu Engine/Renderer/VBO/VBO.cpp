#include "VBO.h"

VBO::VBO()
{
}

VBO::VBO(GLfloat* vertices, GLsizeiptr size)
{
	//Generate the VBO
	glGenBuffers(1, &ID);
	//Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	//Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::Bind()
{
	//Bind VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind()
{
	//Unbind the VBO to 0
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete()
{
	//Delete the VBO object
	glDeleteBuffers(1, &ID);
}