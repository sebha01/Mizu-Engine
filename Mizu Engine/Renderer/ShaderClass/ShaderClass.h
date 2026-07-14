#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "Config.h"

std::string getFileContents(const char* fileName);

class Shader
{
	public:
		//ID of the shader
		GLuint ID;
		//Default constructor
		Shader();
		//Constructor that takes the file paths of frag and vert shader to be used for the shader program
		Shader(const char* vertexFile, const char* fragmentFile);

		//Activates the shader program
		void Activate();
		//Deletes shader program
		void Delete();
	private:
		//Checks if different shaders have compiled
		void compileErrors(unsigned int shader, const char* type);
};

#endif