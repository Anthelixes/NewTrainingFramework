#pragma once
#include <vector>
#include "TextureResource.h"
#include "Vertex.h"
#include "../Utilities/utilities.h"
class Texture
{
private:
	TextureResource * tr;
	GLuint	id;
public:
	void	setTextureResource(TextureResource *tr);
	void	Load();
	GLuint	getId();
	Texture();
	~Texture();
};
