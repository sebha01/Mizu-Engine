#version 330 core



//Positions/coords
layout (location = 0) in vec3 aPos;
//Colours
layout (location = 1) in vec4 aColour;
// Text coords
layout (location = 2) in vec2 aTex;
//Normals
layout (location = 3) in vec3 aNormal;




//Outputs the colour for the fragment shader
out vec4 colour;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;
out vec3 Normal;
out vec3 crntPos;




// Imports the camera matrix from the main function
uniform mat4 camMatrix;
uniform mat4 model;



void main()
{
	crntPos = vec3(model * vec4(aPos, 1.0f));	

	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);
	//Assigns the colours from the vertex data to "colour"
	colour = aColour;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;
	Normal = aNormal;
}