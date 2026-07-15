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

void Renderer::beginDrawProcess(Texture* texture)
{
	//Gets ID of uniform called scale
	uniID = glGetUniformLocation(defaultShaderProgram.ID, "scale");
	//Assigns value to the uniform
	//NOTE: Must always be done after activating the shader program
	glUniform1f(uniID, 0.5f);
	
	if (texture != nullptr)
	{
		//Binds texture so it appears when rendered
		texture->Bind();
	}

	//Bind VAO so OpenGL knows to use it 
	VAO1.Bind();
}

void Renderer::deleteObjectsTexturesAndShaderProgram(Texture* texture, bool hasEBO)
{
	//Delete VAO and VBO
	VAO1.Delete();
	VBO1.Delete();

	//check if the objects relevant to the shape being rendered have an ebo
	if (hasEBO)
	{
		EBO1.Delete();
	}
	
	//Check if the object has a texture
	if (texture != nullptr)
	{
		texture->Delete();
	}

	//Delete the default shader program
	defaultShaderProgram.Delete();
}

void Renderer::setUp2DTriangle()
{
	setUpObjectsAndShaderProgram(defaultVertex2DShaderPath, defaultFragment2DShaderPath, Triangle2DVertices, sizeof(Triangle2DVertices), nullptr, 0, false);
	
	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	
	unbindObjects(false);
}

void Renderer::draw2DTriangle()
{
	beginDrawProcess(nullptr);

	//Draw the triangle using GL_TRIANGLES primitive
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::delete2DTriangleVariables()
{
	//Delete all objects created when rendering the 2D triangle
	deleteObjectsTexturesAndShaderProgram(nullptr, true);
}

void Renderer::setUpIndexBuffer2DTriangle()
{
	setUpObjectsAndShaderProgram(defaultVertex2DShaderPath, defaultFragment2DShaderPath, IndexBuffer2DTriVerts, sizeof(IndexBuffer2DTriVerts), IndexBufferIndices, sizeof(IndexBufferIndices), true);

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	
	unbindObjects(true);
}

void Renderer::drawIndexBuffer2DTriangle()
{
	beginDrawProcess(nullptr);

	//Draw the triangle using GL_TRIANGLES primitive
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
}

void Renderer::deleteIndexBuffer2DTriangleVariables()
{
	//Delete all objects created when rendering the 2D Indices triangle
	deleteObjectsTexturesAndShaderProgram(nullptr, true);
}

void Renderer::setUp2DSquare()
{
	setUpObjectsAndShaderProgram(defaultVertex2DShaderPath, defaultFragment2DShaderPath, squareVertices, sizeof(squareVertices), squareIndices, sizeof(squareIndices), true);

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	
	unbindObjects(true);
}

void Renderer::draw2DSquare()
{
	beginDrawProcess(nullptr);

	//Draw the triangle using GL_TRIANGLES primitive
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::delete2DSquare()
{
	//Delete all objects created when rendering the 2D square
	deleteObjectsTexturesAndShaderProgram(nullptr, true);
}

void Renderer::setUpTexturedQuad()
{
	setUpObjectsAndShaderProgram(defaultVertex2DTextureShaderPath, defaultFragment2DTextureShaderPath, texturedQuadVertices, sizeof(texturedQuadVertices), texturedQuadIndices, sizeof(texturedQuadIndices), true);

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
	beginDrawProcess(&floorTexture);

	//Draw the triangle using GL_TRIANGLES primitive
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::deleteTexturedQuad()
{
	//Delete all objects created when rendering the textured quad
	deleteObjectsTexturesAndShaderProgram(&floorTexture, true);
}

void Renderer::update3DView(const int width, const int height)
{
	//Enables depth buffer
	glEnable(GL_DEPTH_TEST);

	defaultShaderProgram.Activate();

	//Simple timer
	double crntTime = glfwGetTime();
	if (crntTime - prevTime >= 1 / 60)
	{
		rotation += 0.05f;
		prevTime = crntTime;
	}

	//Define the matrices so they are not null
	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	proj = glm::mat4(1.0f);

	//Assign transformations to the matrices
	//Rotate the object in 3D space
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	//Set the world view position slightly back and a bit up
	view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
	//					Field Of View (radians)	Aspect Ratio of screen	closest point /furthest point we can see
	//For now aspect ratio will remain as normal
	proj = glm::perspective(glm::radians(45.0f), (float)(width / height),	0.01f,				1000.0f);


	//Output matrices into the vertex shader
	//model matrix
	modelLoc = glGetUniformLocation(defaultShaderProgram.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	//view matrix
	viewLoc = glGetUniformLocation(defaultShaderProgram.ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	//projection matrix
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
	beginDrawProcess(&limeStoneCliffsTexture);

	//Draw the triangle using GL_TRIANGLES primitive
	glDrawElements(GL_TRIANGLES, sizeof(pyramidIndices)/sizeof(int), GL_UNSIGNED_INT, 0);
}

void Renderer::deletePyramid()
{
	//Delete all objects, textures and shader program associated with the pyramid object
	deleteObjectsTexturesAndShaderProgram(&limeStoneCliffsTexture, true);
}