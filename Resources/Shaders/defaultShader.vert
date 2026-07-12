#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColour;

//Outputs the colour for the fragment shader
out vec4 colour;

uniform float scale;

void main()
{
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	//Assigns the colours from the vertex data to "colour"
	colour = aColour;
}