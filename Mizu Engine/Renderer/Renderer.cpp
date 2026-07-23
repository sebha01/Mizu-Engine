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
	//Check if the texture has an actual value
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

void Renderer::setUpCamera(const int width, const int height)
{
	//Initialise camera object and set its' default values
	camera = Camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));
}

void Renderer::enableCameraInputs(GLFWwindow* window)
{
	//Handles camera inputs
	camera.Inputs(window);
}

void Renderer::setUp2DTriangle()
{
	//Set up relevant objects and shader program to render the triangle
	setUpObjectsAndShaderProgram(defaultVertex2DShaderPath, defaultFragment2DShaderPath, Triangle2DVertices, sizeof(Triangle2DVertices), nullptr, 0, false);
	
	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	
	//Unbind relevant objects used to render the triangle
	unbindObjects(false);
}

void Renderer::draw2DTriangle()
{
	//Start the drawing process for the triangle
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
	//Set up objects and shader program to use when rendering the index buffer triangle
	setUpObjectsAndShaderProgram(defaultVertex2DShaderPath, defaultFragment2DShaderPath, IndexBuffer2DTriVerts, sizeof(IndexBuffer2DTriVerts), IndexBufferIndices, sizeof(IndexBufferIndices), true);

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	
	//Unbind objects associated with rendering the index buffer triangle
	unbindObjects(true);
}

void Renderer::drawIndexBuffer2DTriangle()
{
	//begin the draw process for the index buffer triangle
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
	//Set up objects and shader program to render the quad
	setUpObjectsAndShaderProgram(defaultVertex2DShaderPath, defaultFragment2DShaderPath, squareVertices, sizeof(squareVertices), squareIndices, sizeof(squareIndices), true);

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 7 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	
	//Unbind the objects associated with rendering the quad
	unbindObjects(true);
}

void Renderer::draw2DSquare()
{
	//Begin the drawing process for the quad
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
	//Set up objects and shader program to render the textured quad
	setUpObjectsAndShaderProgram(defaultVertex2DTextureShaderPath, defaultFragment2DTextureShaderPath, texturedQuadVertices, sizeof(texturedQuadVertices), texturedQuadIndices, sizeof(texturedQuadIndices), true);

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 9 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(GLfloat), (void*)(7 * sizeof(float)));
	
	//Unbind the objects associated with rendering the textured quad
	unbindObjects(true);

	//floor texture object
	floorTexture = Texture("../../../Resources/Textures/AngledBlocksFloor/angled-blocks-vegetation_albedo.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
}

void Renderer::drawTexturedQuad()
{
	//Begin the draw process for rendering the textured quad
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

	// Updates and exports the camera matrix to the Vertex Shader
	camera.updateMatrix(45.0f, 0.1f, 100.0f);

	//Activate default shader program
	defaultShaderProgram.Activate();
	camera.Matrix(defaultShaderProgram, "camMatrix");
}

void Renderer::setUpPyramid()
{
	//Set up objects and shader program to render the 3D pyramid
	setUpObjectsAndShaderProgram(defaultVertex3DShaderPath, defaultFragment3DShaderPath, pyramidVertices, sizeof(pyramidVertices), pyramidIndices, sizeof(pyramidIndices), true);

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 9 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 9 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 9 * sizeof(GLfloat), (void*)(7 * sizeof(float)));
	
	//Unbind the objects
	unbindObjects(true);

	//floor texture object
	limeStoneCliffsTexture = Texture("../../../Resources/Textures/LimestoneCliffs/limestone-cliffs_albedo.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
}

void Renderer::drawPyramid()
{
	//Begin drawing process for 3D pyramid
	beginDrawProcess(&limeStoneCliffsTexture);

	//Draw the triangle using GL_TRIANGLES primitive
	glDrawElements(GL_TRIANGLES, sizeof(pyramidIndices)/sizeof(int), GL_UNSIGNED_INT, 0);
}

void Renderer::deletePyramid()
{
	//Delete all objects, textures and shader program associated with the pyramid object
	deleteObjectsTexturesAndShaderProgram(&limeStoneCliffsTexture, true);
}

void Renderer::setUpLitPyramid()
{
	//Set up objects and shader program to render the 3D pyramid
	setUpObjectsAndShaderProgram(litVertex3DShaderPath, litFragment3DShaderPath, diffuseObjectVertices, sizeof(diffuseObjectVertices), diffuseObjectIndices, sizeof(diffuseObjectIndices), true);

	//Links the VBO attributes such as colour and coordinates to the VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 12 * sizeof(GLfloat), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 12 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 12 * sizeof(GLfloat), (void*)(7 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 12 * sizeof(GLfloat), (void*)(9 * sizeof(float)));

	//Unbind the objects
	unbindObjects(true);

	//floor texture object
	limeStoneCliffsTexture = Texture("../../../Resources/Textures/LimestoneCliffs/limestone-cliffs_albedo.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);


	//Light stuff
	lightShader = Shader(defaultLightVertexShaderPath, defaultLightFragmentShaderPath);
	// Generates Vertex Array Object and binds it
	lightVAO.Create();
	lightVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	lightVBO = VBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	lightEBO = EBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	glm::vec4 lightColour = glm::vec4(white.r, white.g, white.b, white.a);

	lightModel = glm::translate(lightModel, lightPos);
	pyramidModel = glm::translate(pyramidModel, pyramidPos);

	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColour"), lightColour.x, lightColour.y, lightColour.z, lightColour.w);
	defaultShaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(defaultShaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
	glUniform4f(glGetUniformLocation(defaultShaderProgram.ID, "lightColour"), lightColour.x, lightColour.y, lightColour.z, lightColour.w);
	glUniform3f(glGetUniformLocation(defaultShaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
}

void Renderer::drawLitPyramid()
{
	// Tells OpenGL which Shader Program we want to use
	defaultShaderProgram.Activate();
	// Exports the camera Position to the Fragment Shader for specular lighting
	glUniform3f(glGetUniformLocation(defaultShaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	// Export the camMatrix to the Vertex Shader of the pyramid
	camera.Matrix(defaultShaderProgram, "camMatrix");

	//Begin drawing process for 3D pyramid
	beginDrawProcess(&limeStoneCliffsTexture);

	//Draw the triangle using GL_TRIANGLES primitive
	glDrawElements(GL_TRIANGLES, sizeof(diffuseObjectIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

	// Tells OpenGL which Shader Program we want to use
	lightShader.Activate();
	// Export the camMatrix to the Vertex Shader of the light cube
	camera.Matrix(lightShader, "camMatrix");
	// Bind the VAO so OpenGL knows to use it
	lightVAO.Bind();
	// Draw primitives, number of indices, datatype of indices, index of indices
	glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
}

void Renderer::deleteLitPyramid()
{
	//Delete all objects, textures and shader program associated with the pyramid object
	deleteObjectsTexturesAndShaderProgram(&limeStoneCliffsTexture, true);
}
