#pragma once
#include "ShaderResource.h"

#include "../Utilities/esUtil.h"
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
	GLuint	uvblendAttribute;
	GLuint	rUniform;
	GLuint	RUniform;
	GLuint	camUniform;
	GLuint	worldUniform;
	GLuint	uTimeUniform;
	GLuint	dispMaxUniform;
	GLuint	heightUniform;
	GLuint	skyboxUniform;

	GLuint	ambUniform;
	GLuint	normAttribute;
	GLuint	diffColorUniform;
	GLuint	specColorUniform;
	GLuint	diffDirectionUniform;
	GLuint	diffPositionUniform;
	GLuint	ratioUniform;
	GLuint	specPowerUniform;
	GLuint	lightTypeUniform;
	GLuint	spotLightPositionUniform;
	GLuint	spotLightOpeningUniform;
	GLuint	spotLightDirectionUniform;
	void	setShaderResource(ShaderResource *);
	void	Load();
	~Shader();
};