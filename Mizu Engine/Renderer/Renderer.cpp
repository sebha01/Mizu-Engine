#include "Renderer.h"

Renderer::Renderer()
{	
}

Renderer::~Renderer()
{
}

void Renderer::setUp2DTriangle()
{
	//Create VAO
	VAO1.Create();
	//Bind the VAO
	VAO1.Bind();

	//Create the shader program
	defaultShaderProgram = Shader(vertexShaderPath, fragmentShaderPath);
	//Create the VBO
	VBO1 = VBO(Triangle2DVertices, sizeof(Triangle2DVertices));
	
	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	//Unbind VAO
	VAO1.Unbind();
	//Unbind VBO
	VBO1.Unbind();
}

void Renderer::draw2DTriangle()
{
	//Gets ID of uniform called scale
	uniID = glGetUniformLocation(defaultShaderProgram.ID, "scale");
	//Tell OpenGL which shader program to use
	defaultShaderProgram.Activate();
	//Assigns value to the uniform
	//NOTE: Must always be done after activating the shader program
	glUniform1f(uniID, 0.5f);
	//Bind VAO so OpenGL knows to use it 
	VAO1.Bind();
	//Draw the triangle using GL_TRIANGLES primitive
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::delete2DTriangleVariables()
{
	//Delete all objects created when rendering the 2D triangle
	VAO1.Delete();
	VBO1.Delete();
	defaultShaderProgram.Delete();
}

void Renderer::setUpIndexBuffer2DTriangle()
{
	//Create VAO
	VAO1.Create();
	//Bind the VAO
	VAO1.Bind();

	//Create shader program
	defaultShaderProgram = Shader(vertexShaderPath, fragmentShaderPath);
	//Create VBO
	VBO1 = VBO(IndexBuffer2DTriVerts, sizeof(IndexBuffer2DTriVerts));
	//Create EBO
	EBO1 = EBO(IndexBufferIndices, sizeof(IndexBufferIndices));

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	//Unbond VAO
	VAO1.Unbind();
	//Unbind VBO
	VBO1.Unbind();
	//Unbind EBO
	EBO1.Unbind();
}

void Renderer::drawIndexBuffer2DTriangle()
{
	//Gets ID of uniform called scale
	uniID = glGetUniformLocation(defaultShaderProgram.ID, "scale");
	//Tell OpenGL which shader program to use
	defaultShaderProgram.Activate();
	//Assigns value to the uniform
	//NOTE: Must always be done after activating the shader program
	glUniform1f(uniID, 0.5f);
	//Bind VAO so OpenGL knows to use it 
	VAO1.Bind();
	//Draw the triangle using GL_TRIANGLES primitive
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}

void Renderer::deleteIndexBuffer2DTriangleVariables()
{
	//Delete all objects created when rendering the 2D Indices triangle
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
}

void Renderer::setUp2DSquare()
{
	//Create VAO
	VAO1.Create();
	//Bind the VAO
	VAO1.Bind();

	//Create shader program
	defaultShaderProgram = Shader(vertexShaderPath, fragmentShaderPath);
	//Create VBO
	VBO1 = VBO(squareVertices, sizeof(squareVertices));
	//Create EBO
	EBO1 = EBO(squareIndices, sizeof(squareIndices));

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	//Unbond VAO
	VAO1.Unbind();
	//Unbind VBO
	VBO1.Unbind();
	//Unbind EBO
	EBO1.Unbind();
}

void Renderer::draw2DSquare()
{
	//Gets ID of uniform called scale
	uniID = glGetUniformLocation(defaultShaderProgram.ID, "scale");
	//Tell OpenGL which shader program to use
	defaultShaderProgram.Activate();
	//Assigns value to the uniform
	//NOTE: Must always be done after activating the shader program
	glUniform1f(uniID, 0.5f);
	//Bind VAO so OpenGL knows to use it 
	VAO1.Bind();
	//Draw the triangle using GL_TRIANGLES primitive
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::delete2DSquare()
{
	//Delete all objects created when rendering the 2D Indices triangle
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
}

void Renderer::setUpTexturedQuad()
{
	//Create VAO
	VAO1.Create();
	//Bind the VAO
	VAO1.Bind();

	//Create shader program
	defaultShaderProgram = Shader(vertexShaderPath, fragmentShaderPath);
	//Create VBO
	VBO1 = VBO(squareVertices, sizeof(squareVertices));
	//Create EBO
	EBO1 = EBO(squareIndices, sizeof(squareIndices));

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 9 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(GLfloat), (void*)(7 * sizeof(float)));
	//Unbond VAO
	VAO1.Unbind();
	//Unbind VBO
	VBO1.Unbind();
	//Unbind EBO
	EBO1.Unbind();

	bytes = stbi_load("../../../Resources/Textures/AngledBlocksFloor/angled-blocks-vegetation_albedo.png", &widthImg, &heightImg, &numColCh, STBI_rgb_alpha);
	std::cout << "Loading texture..." << std::endl;

	if (!bytes)
	{
		std::cout << "Texture failed to load: " << stbi_failure_reason() << std::endl;
		return;
	}
	else
	{
		std::cout << "Texture loaded." << std::endl;
	}

	//Flip the texture because stbi reads the image in reverse compared to openGL
	stbi_set_flip_vertically_on_load(true);

	glGenTextures(1, &floorTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, floorTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::drawTexturedQuad()
{
	//Gets ID of uniform called scale
	uniID = glGetUniformLocation(defaultShaderProgram.ID, "scale");
	//Get ID of uniform called tex0
	tex0Uni = glGetUniformLocation(defaultShaderProgram.ID, "tex0");
	//Tell OpenGL which shader program to use
	defaultShaderProgram.Activate();
	glUniform1i(tex0Uni, 0);
	//Assigns value to the uniform
	//NOTE: Must always be done after activating the shader program
	glUniform1f(uniID, 0.5f);
	glBindTexture(GL_TEXTURE_2D, floorTexture);
	//Bind VAO so OpenGL knows to use it 
	VAO1.Bind();
	//Draw the triangle using GL_TRIANGLES primitive
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::deleteTexturedQuad()
{
	//Delete all objects created when rendering the 2D Indices triangle
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	glDeleteTextures(1, &floorTexture);
}