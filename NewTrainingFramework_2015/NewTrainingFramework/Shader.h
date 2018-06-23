#pragma once
#include "ShaderResource.h"
#include "../Utilities/utilities.h"

class Shader
{
private:
	ShaderResource * sr;
	GLuint	id;
public:
	Shader();
	int Init(char * fileVertexShader, char * fileFragmentShader);
	GLuint	getId();
	GLuint	positionAttribute;
	GLuint	matrixUniform;
	GLuint	textureUniform[5];
	GLuint	uvAttribute;

	void	setShaderResource(ShaderResource *);
	void	Load();
	~Shader();
};