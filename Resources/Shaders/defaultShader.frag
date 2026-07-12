#version 330 core

out vec4 FragColor;

//Inputs the colour from the vertex shader
in vec4 colour;

void main()
{
	FragColor = vec4(colour);
}