#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "Config.h"

class VBO
{
	public:
		//Reference ID of the Vertex Buffer Object
		GLuint ID;
		// Default Constructor
		VBO();
		// Constructor that generates a VBO and links it to the vertices
		VBO(GLfloat* vertices, GLsizeiptr size);

		//Binds VBO
		void Bind();
		//Unbinds VBO
		void Unbind();
		//Deletes VBO
		void Delete();
};

#endif