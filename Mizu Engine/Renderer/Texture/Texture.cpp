#include "Texture.h"

Texture::Texture()
{

}

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
	type = texType;

	//Textures
	int widthImg = 0;
	int heightImg = 0;
	int numColCh = 0;
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, STBI_rgb_alpha);
	
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

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
	glGenerateMipmap(texType);

	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader shader, const char* uniform, GLuint unit)
{
	//Get ID of uniform called tex0
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	//Tell OpenGL which shader program to use
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}