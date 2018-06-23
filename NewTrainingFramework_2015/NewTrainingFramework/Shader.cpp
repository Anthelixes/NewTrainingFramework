#include "stdafx.h"
#include "Shader.h"

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
	//id e vechiul "program" din Shaders.cpp
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