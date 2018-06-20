#pragma once
#include "ShaderResource.h"
#include <vector>
#include "Vertex.h"
#include "../Utilities/utilities.h"

class Shader
{
private:
	ShaderResource * mr;
	GLuint	id;
public:
	Shader();
	GLuint	getId();
	void	Load();
	~Shader();
};

