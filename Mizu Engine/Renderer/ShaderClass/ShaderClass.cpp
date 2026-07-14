#include "ShaderClass.h"

std::string getFileContents(const char* fileName)
{
	std::ifstream in(fileName, std::ios::binary);

	std::cout << "Trying to open: " << fileName << std::endl;
	std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

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

Shader::Shader()
{
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
	//Checks if shader compiled successfully
	compileErrors(vertexShader, "VERTEX");

	//Create fragment shader object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach fragment shader source to the vertex shader object
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//Compile the vertex shader into machine code
	glCompileShader(fragmentShader);
	//Checks if shader compiled successfully
	compileErrors(fragmentShader, "FRAGMENT");

	//Create shader program object and get reference
	ID = glCreateProgram();
	//Attach vertex and fragment shaders to the shader program object
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	//Link all shaders together into the shader program
	glLinkProgram(ID);
	//Checks if shaders linked successfully
	compileErrors(ID, "PROGRAM");

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

void Shader::compileErrors(unsigned int shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);

		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_COMPILE_STATUS, &hasCompiled);

		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << std::endl;
		}
	}
}
