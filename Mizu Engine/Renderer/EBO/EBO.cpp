#include "EBO.h"

EBO::EBO()
{
}

//Constructor that genereates an EBO and linkes it to indices
EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	//Generate the VBO
	glGenBuffers(1, &ID);
	//Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	//Introduce the vertices into the VBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind()
{
	//Bind VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind()
{
	//Unbind the VBO to 0
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete()
{
	//Delete the VBO object
	glDeleteBuffers(1, &ID);
}