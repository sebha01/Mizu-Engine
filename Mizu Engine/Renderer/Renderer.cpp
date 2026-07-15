#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::setUpObjectsAndShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath, GLfloat verts[], GLsizeiptr vertsSize, GLuint indices[], GLsizeiptr indicesSize, bool hasEBO)
{
	//Create VAO
	VAO1.Create();
	//Bind the VAO
	VAO1.Bind();

	//Create shader program
	defaultShaderProgram = Shader(vertexShaderPath, fragmentShaderPath);
	//Create VBO
	VBO1 = VBO(verts, vertsSize);
	
	if (hasEBO)
	{
		//Create EBO
		EBO1 = EBO(indices, indicesSize);
	}
}

void Renderer::unbindObjects(bool hasEBO)
{
	//Unbond VAO
	VAO1.Unbind();
	//Unbind VBO
	VBO1.Unbind();

	if (hasEBO)
	{
		//Unbind EBO
		EBO1.Unbind();
	}
}

void Renderer::setUp2DTriangle()
{
	//Create VAO
	VAO1.Create();
	//Bind the VAO
	VAO1.Bind();

	//Create the shader program
	defaultShaderProgram = Shader(defaultVertex2DShaderPath, defaultFragment2DShaderPath);
	//Create the VBO
	VBO1 = VBO(Triangle2DVertices, sizeof(Triangle2DVertices));
	
	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	
	unbindObjects(false);
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
	defaultShaderProgram = Shader(defaultVertex2DShaderPath, defaultFragment2DShaderPath);
	//Create VBO
	VBO1 = VBO(IndexBuffer2DTriVerts, sizeof(IndexBuffer2DTriVerts));
	//Create EBO
	EBO1 = EBO(IndexBufferIndices, sizeof(IndexBufferIndices));

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	
	unbindObjects(true);
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
	defaultShaderProgram = Shader(defaultVertex2DShaderPath, defaultFragment2DShaderPath);
	//Create VBO
	VBO1 = VBO(squareVertices, sizeof(squareVertices));
	//Create EBO
	EBO1 = EBO(squareIndices, sizeof(squareIndices));

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	
	unbindObjects(true);
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
	//Delete all objects created when rendering the 2D square
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
	defaultShaderProgram = Shader(defaultVertex2DShaderPath, defaultFragment2DShaderPath);
	//Create VBO
	VBO1 = VBO(squareVertices, sizeof(squareVertices));
	//Create EBO
	EBO1 = EBO(squareIndices, sizeof(squareIndices));

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 9 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(GLfloat), (void*)(7 * sizeof(float)));
	
	unbindObjects(true);

	//floor texture object
	floorTexture = Texture("../../../Resources/Textures/AngledBlocksFloor/angled-blocks-vegetation_albedo.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
}

void Renderer::drawTexturedQuad()
{
	//Gets ID of uniform called scale
	uniID = glGetUniformLocation(defaultShaderProgram.ID, "scale");
	//Get uniform ID for tex0 and tell openGL which shader to use
	floorTexture.texUnit(defaultShaderProgram, "tex0", 0);
	//Assigns value to the uniform
	//NOTE: Must always be done after activating the shader program
	glUniform1f(uniID, 0.5f);
	//Binds texture so it appears when rendered
	floorTexture.Bind();
	//Bind VAO so OpenGL knows to use it 
	VAO1.Bind();
	//Draw the triangle using GL_TRIANGLES primitive
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::deleteTexturedQuad()
{
	//Delete all objects created when rendering the textured quad
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	floorTexture.Delete();
}

void Renderer::update3DView(const int width, const int height)
{
	defaultShaderProgram.Activate();

	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	proj = glm::mat4(1.0f);

	//Set the world view position slightly back and a bit up
	view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
	//					Field Of View (radians)	Aspect Ratio of screen	closest point /furthest point we can see
	//For now aspect ratio will remain as normal
	proj = glm::perspective(glm::radians(45.0f), (float)(width / height),	0.01f,				1000.0f);

	modelLoc = glGetUniformLocation(defaultShaderProgram.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	viewLoc = glGetUniformLocation(defaultShaderProgram.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	projLoc = glGetUniformLocation(defaultShaderProgram.ID, "proj");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

}

void Renderer::setUpPyramid()
{
	setUpObjectsAndShaderProgram(defaultVertex3DShaderPath, defaultFragment3DShaderPath, pyramidVertices, sizeof(pyramidVertices), pyramidIndices, sizeof(pyramidIndices), true);

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 9 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(GLfloat), (void*)(7 * sizeof(float)));
	
	unbindObjects(true);

	//floor texture object
	limeStoneCliffsTexture = Texture("../../../Resources/Textures/LimestoneCliffs/limestone-cliffs_albedo.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
}

void Renderer::drawPyramid()
{
	//Gets ID of uniform called scale
	uniID = glGetUniformLocation(defaultShaderProgram.ID, "scale");
	//Assigns value to the uniform
	//NOTE: Must always be done after activating the shader program
	glUniform1f(uniID, 0.5f);

	//Binds texture so it appears when rendered
	limeStoneCliffsTexture.Bind();
	
	//Bind VAO so OpenGL knows to use it 
	VAO1.Bind();
	//Draw the triangle using GL_TRIANGLES primitive
	glDrawElements(GL_TRIANGLES, sizeof(pyramidIndices)/sizeof(int), GL_UNSIGNED_INT, 0);
}
