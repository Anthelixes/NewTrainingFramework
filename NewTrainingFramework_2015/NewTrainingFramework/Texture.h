#pragma once
#include "TextureResource.h"
#include <vector>
#include "Vertex.h"
#include "../Utilities/utilities.h"
class Texture
{
private:
	TextureResource * tr;
	GLuint	id;
public:
	void	Load();
	GLuint	getId();
	Texture();
	~Texture();
};

