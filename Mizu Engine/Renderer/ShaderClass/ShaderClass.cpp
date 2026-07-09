#include "ShaderClass.h"

std::string getFileContents(const char* fileName)
{
	std::ifstream in(fileName, std::ios::binary);

	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	std::string vertexCode = getFileContents(vertexFile);
	std::string fragmentCode = getFileContents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//Create vertex shader object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach vertex shader source to the vertex shader object
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//Compile the vertex shader into machine code
	glCompileShader(vertexShader);

	//Create fragment shader object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach fragment shader source to the vertex shader object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//Compile the vertex shader into machine code
	glCompileShader(fragmentShader);

	//Create shader program object and get reference
	ID = glCreateProgram();
	//Attach vertex and fragment shaders to the shader program object
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//Link all shaders together into the shader program
	glLinkProgram(ID);

	//Delete the shader objects now they are not needed anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Activate()
{
	glUseProgram(ID);
}

void Shader::Delete()
{
	glDeleteProgram(ID);
}