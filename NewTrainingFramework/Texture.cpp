#include "stdafx.h"
#include "Texture.h"
#include "../Utilities/utilities.h"


void Texture::setTextureResource(TextureResource *textureResource) {
	tr = textureResource;
}

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

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, array_pixels);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else if (strcmp(tr->type.c_str(), "3d") == 0) {
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_CUBE_MAP, id);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		int	offsetW = height * width / 4 * bpp / 8;
		int	offsetH = width * height / 3 * bpp / 8;
		int	N = width / 4 * bpp / 8;
		char*	buff = new char[height / 3 * width / 4 * bpp / 8];

		for (int i = 0; i < height / 3; i++)
		{
			for (int j = 0; j < N; j++)
			{
				buff[i * N + j] = array_pixels[offsetW / height + i * width * bpp / 8 + j];
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)buff);

		for (int i = 0; i < height / 3; i++)
		{
			for (int j = 0; j < N; j++)
			{
				buff[i * N + j] = array_pixels[offsetH  + i * width * bpp / 8 + j];
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)buff);

		for (int i = 0; i < height / 3; i++)
		{
			for (int j = 0; j < N; j++)
			{
				buff[i * N + j] = array_pixels[offsetH + offsetW / height + i * width * bpp / 8 + j];
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)buff);

		for (int i = 0; i < height / 3; i++)
		{
			for (int j = 0; j < N; j++)
			{
				buff[i * N + j] = array_pixels[offsetH + 2 * offsetW / height + i * width * bpp / 8 + j];
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)buff);

		for (int i = 0; i < height / 3; i++)
		{
			for (int j = 0; j < N; j++)
			{
				buff[i * N + j] = array_pixels[offsetH + 3 * offsetW / height + i * width * bpp / 8 + j];
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)buff);

		for (int i = 0; i < height / 3; i++)
		{
			for (int j = 0; j < N; j++)
			{
				buff[i * N + j] = array_pixels[2 * offsetH + offsetW / height + i * width * bpp / 8 + j];
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, format, width / 4, height / 3, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)buff);


		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
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