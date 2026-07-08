#include "Renderer.h"

//Shaders
//Vertex Shader Source Code
const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";
//Fragment shader source code
const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::setUp2DTriangle()
{
	//Create vertex shader object and get its reference
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach vertex shader source to the vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//Compile the vertex shader into machine code
	glCompileShader(vertexShader);

	//Create fragment shader object and get its reference
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach fragment shader source to the vertex shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Compile the vertex shader into machine code
	glCompileShader(fragmentShader);

	//Create shader program object and get reference
	shaderProgram = glCreateProgram();
	//Attach vertex and fragment shaders to the shader program object
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//Link all shaders together into the shader program
	glLinkProgram(shaderProgram);

	//Delete the shader objects now they are not needed anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Make the VAO the current Vertex Array Object by binding it
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle2DVertices), Triangle2DVertices, GL_STATIC_DRAW);

	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	// Enable the Vertex Attribute so that OpenGL knows to use it
	glEnableVertexAttribArray(0);

	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::draw2DTriangle()
{
	//Tell OpenGL which shader program to use
	glUseProgram(shaderProgram);
	//Bind VAO so OpenGL knows to use it 
	glBindVertexArray(VAO);
	//Draw the triangle using GL_TRIANGLES primitive
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::delete2DTriangleVariables()
{
	//Delete all objects created when rendering the 2D triangle
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
}

void Renderer::setUpIndexBuffer2DTriangle()
{

}

void Renderer::drawIndexBuffer2DTriangle()
{

}

void Renderer::deleteIndexBuffer2DTriangleVariables()
{

}
