#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "Config.h"

std::string getFileContents(const char* fileName);

class Shader
{
	public:
		GLuint ID;
		Shader(const char* vertexFile, const char* fragmentFile);

		void Activate();
		void Delete();
};

#endif