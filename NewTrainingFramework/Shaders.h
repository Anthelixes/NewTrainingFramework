#pragma once
#include "../Utilities/esUtil.h"
class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint matrixUniform;
	GLint textureUniform;
	GLint uvAttribute;

	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};