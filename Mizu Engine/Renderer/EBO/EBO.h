#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include "Config.h"

class EBO
{
	public:
		//ID reference of Elements Buffer Object
		GLuint ID;
		//Default constructor
		EBO();
		//Constructor
		EBO(GLuint* indices, GLsizeiptr size);

		//Binds EBO
		void Bind();
		//Unbinds EBO
		void Unbind();
		//Deletes EBO
		void Delete();
};

#endif