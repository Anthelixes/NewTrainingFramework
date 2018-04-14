// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include "Camera.h"



GLuint vboId;
Shaders myShaders;
Shaders lineShaders;
Camera x;

int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	//triangle data (heap)
	Vertex verticesData[6];

	verticesData[0].pos.x = -0.5f;  verticesData[0].pos.y =  0.5f;  verticesData[0].pos.z =  0.0f;
	verticesData[1].pos.x = -0.5f;  verticesData[1].pos.y = -0.5f;  verticesData[1].pos.z =  0.0f;
	verticesData[2].pos.x =  0.5f;  verticesData[2].pos.y = -0.5f;  verticesData[2].pos.z =  0.0f;
	
	verticesData[3].pos.x = 0.5f;	verticesData[3].pos.y = -0.5f;  verticesData[3].pos.z = 0.0f;
	verticesData[4].pos.x = -0.5f;	verticesData[4].pos.y = 0.5f;	verticesData[4].pos.z = 0.0f;
	verticesData[5].pos.x = 0.5f;	verticesData[5].pos.y = 0.5f;	verticesData[5].pos.z = 0.0f;

	verticesData[0].color.x = 0.0f;  verticesData[0].color.y = 0.0f;  verticesData[0].color.z = 1.0f; // 
	verticesData[1].color.x = 0.0f;  verticesData[1].color.y = 1.0f;  verticesData[1].color.z = 0.0f; //verde drp jos
	verticesData[2].color.x = 1.0f;  verticesData[2].color.y = 0.0f;  verticesData[2].color.z = 0.0f; //rosu
	
	verticesData[3].color.x = 1.0f;	 verticesData[3].color.y = 0.0f;  verticesData[3].color.z = 0.0f;
	verticesData[4].color.x = 0.0f;	 verticesData[4].color.y = 0.0f;  verticesData[4].color.z = 1.0f;
	verticesData[5].color.x = 1.0f;	 verticesData[5].color.y = 0.0f;  verticesData[5].color.z = 1.0f;
	
	//buffer object
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

}

float alfa = 0.01;

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(myShaders.program);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	Matrix mr, P;
	Matrix mvp;

	alfa += 0.01;
	mvp = x.viewMatrix * x.Perspect;
	//P.SetPerspective(x.getFOV(), (GLfloat)Globals::screenWidth / Globals::screenHeight, x.getNear(), x.getFar());
	//mr = mr * P;

	if(myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (myShaders.colorAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.colorAttribute);
		glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	}

	if (myShaders.matrixUniform != -1)
	{
		glUniformMatrix4fv(myShaders.matrixUniform, 1, GL_FALSE, (GLfloat*) mvp.m);
	}

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	x.setDeltaTime(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	switch (key)
	{
	case 'W':
		x.moveOz(-1);
		break;
	case 'S':
		x.moveOz(1);
		break;
	case 'Q':
		x.moveOy(1);
		break;
	case 'E':
		x.moveOy(-1);
		break;
	case 'A':
		x.moveOx(1);
		break;
	case 'D':
		x.moveOx(-1);
		break;
	case 'I':
		x.rotateOx(1);
		break;
	case 'L':
		x.rotateOy(-1);
		break;
	case 'K':
		x.rotateOx(-1);
		break;
	case 'J':
		x.rotateOy(1);
		break;
	case 'U':
		x.rotateOz(1);
		break;
	case 'O':
		x.rotateOz(-1);
		break;
	default:
		break;
	}
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();


	printf("Press any key...\n");
	_getch();

	
	return 0;
}

