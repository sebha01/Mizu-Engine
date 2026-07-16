#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "Config.h"
#include "../VBO/VBO.h"

class VAO
{
	public:
		//ID reference for Vertex Array Object
		GLuint ID;

		//Default Constructor
		VAO();

		//Generates a VAO ID
		void Create();
		//Links a VBO to the VAO using a certain layout
		void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		//Binds VAO
		void Bind();
		//Unbinds VAO
		void Unbind();
		//Deletes VAO
		void Delete();
};

#endif