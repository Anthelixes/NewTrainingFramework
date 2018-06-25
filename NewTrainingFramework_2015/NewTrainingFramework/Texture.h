#pragma once
#include <vector>
#include "TextureResource.h"
#include "../Utilities/esUtil.h"
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
