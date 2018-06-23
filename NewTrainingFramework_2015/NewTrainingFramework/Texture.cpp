#include "stdafx.h"
#include "Texture.h"

void Texture::setTextureResource(TextureResource *textureResource) {
	tr = textureResource;
}

//IN LUCRU - TREBUIE PT type= 2d / 3d;
void Texture::Load() {
	char*	array_pixels;
	GLint	width, height, bpp;
	GLuint	format;

	array_pixels = LoadTGA( (char*)("../" + tr->path).c_str(), &width, &height, &bpp);

	if (bpp == 24) {
		format = GL_RGB;
	}
	else {
		format = GL_RGBA;
	}
	
	if (strcmp(tr->type.c_str(), "2d") == 0) {
		glGenTextures(1, &id);//
		glBindTexture(GL_TEXTURE_2D, id);//
		if (strcmp(tr->mag_filter.c_str(), "LINEAR") == 0)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		else
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		if (strcmp(tr->min_filter.c_str(), "LINEAR") == 0)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		else
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		if (strcmp(tr->wrap_s.c_str(), "CLAMP_TO_EDGE") == 0)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		else 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		if (strcmp(tr->wrap_t.c_str(), "CLAMP_TO_EDGE") == 0)
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		else
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//glGenTextures(1, &id);//
		//glBindTexture(GL_TEXTURE_2D, id);//
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, array_pixels);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

GLuint Texture::getId() {
	return id;
}

Texture::Texture()
{
}


Texture::~Texture()
{
}