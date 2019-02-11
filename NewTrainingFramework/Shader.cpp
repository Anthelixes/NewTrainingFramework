#include "stdafx.h"
#include "Shader.h"
#include "../Utilities/utilities.h"


void Shader::setShaderResource(ShaderResource *shaderResource) {
	sr = shaderResource;
}

void Shader::Load() {
	GLuint vertexShader;
	GLuint fragmentShader;
	
	vertexShader = esLoadShader(GL_VERTEX_SHADER, (char*)("../" + sr->vs).c_str()); // .. , fileVertexShader

	if (vertexShader == 0)
		std::cout << "Eroare vs";

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, (char*)("../" + sr->fs).c_str() ); // .. , fileFragmentShader

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		std::cout << "Eroare fs";
	}
	id = esLoadProgram(vertexShader, fragmentShader);
	
	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(id, "a_posL");
	matrixUniform = glGetUniformLocation(id, "u_mr");
	//textureUniform = glGetUniformLocation(id, "u_texture");
	textureUniform[0] = glGetUniformLocation(id, "u_texture0");
	textureUniform[1] = glGetUniformLocation(id, "u_texture1");
	textureUniform[2] = glGetUniformLocation(id, "u_texture2");
	textureUniform[3] = glGetUniformLocation(id, "u_texture3");
	textureUniform[4] = glGetUniformLocation(id, "u_texture4");
	uvAttribute = glGetAttribLocation(id, "a_uv");
	uvblendAttribute = glGetAttribLocation(id, "a_uv_blend");
	rUniform = glGetUniformLocation(id, "u_r");
	RUniform = glGetUniformLocation(id, "u_R");
	camUniform = glGetUniformLocation(id, "u_cam");
	worldUniform = glGetUniformLocation(id, "u_world");
	uTimeUniform = glGetUniformLocation(id, "u_time");//foc
	dispMaxUniform = glGetUniformLocation(id, "u_dispMax");//foc
	heightUniform = glGetUniformLocation(id, "u_height");
	skyboxUniform = glGetUniformLocation(id, "u_cube_texture");
	lightTypeUniform = glGetUniformLocation(id, "u_lights_type");

	ambUniform = glGetUniformLocation(id, "c_amb");
	normAttribute = glGetAttribLocation(id, "a_norm");
	diffColorUniform = glGetUniformLocation(id, "c_luminaDiff");
	specColorUniform = glGetUniformLocation(id, "c_luminaSpec");
	diffDirectionUniform = glGetUniformLocation(id, "L");
	diffPositionUniform = glGetUniformLocation(id, "LPoint");
	ratioUniform = glGetUniformLocation(id, "ratio");
	specPowerUniform = glGetUniformLocation(id, "specPower");
	spotLightPositionUniform = glGetUniformLocation(id, "u_spot_pos");
	spotLightOpeningUniform = glGetUniformLocation(id, "u_spot_opening");
	spotLightDirectionUniform = glGetUniformLocation(id, "u_spot_direction");
}

GLuint Shader::getId() {
	return id;
}

Shader::Shader()
{
}


Shader::~Shader()
{
}