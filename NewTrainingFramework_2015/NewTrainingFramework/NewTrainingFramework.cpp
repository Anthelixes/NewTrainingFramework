// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <string>
#include <vector>
#include <cstdio>
#include <sstream>
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "../Utilities/esUtil.h"



Camera			x;
GLuint			vboId;
GLuint			lineId;
GLuint			texturaId; //pt textura
GLuint			modelId; //pt vertecsi
GLuint			indiciId; //pt indici
Shaders			myShaders; //pt triunghi
Shaders			lineShaders; //pt linie
Shaders			myModel; //pt model
Vertex*			model; //vector de vertecsi
int				nrVertices;
int				nrIndices;
unsigned short*	vIndices;
void			parsare();

char*	array_pixels;
GLint	width, height, bpp;
GLuint	format;

int Init ( ESContext *esContext )
{
	glEnable(GL_DEPTH_TEST);
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	//triangle data (heap)
	
	parsare();

	//buffer object
	
	//pentru model
	glGenBuffers(1, &modelId);
	glBindBuffer(GL_ARRAY_BUFFER, modelId);
	glBufferData(GL_ARRAY_BUFFER, nrVertices*sizeof(Vertex), model, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indiciId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndices*sizeof(unsigned short), vIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//end model

	//5.5
	array_pixels = LoadTGA("../Resources/Textures/witch.tga", &width, &height, &bpp);
	if (bpp == 24) {
		format = GL_RGB;
	}
	else {
		format = GL_RGBA;
	}
	glGenTextures(1, &texturaId);//
	glBindTexture(GL_TEXTURE_2D, texturaId);//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (GLvoid *)array_pixels);
	glBindTexture(GL_TEXTURE_2D, 0);
	//end 5.5

	//creation of shaders and program 
	myModel.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	lineShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
}

void parsare() {
	std::ifstream fs;
	fs.open("../Resources/Models/witch.nfg");
	if (!fs)
		std::cout << "Unable to open\n" << std::endl;
	std::string str;
	std::string aux;
	std::getline(fs, str);
	std::cout << str << std::endl;
	aux = str.substr(12);
	nrVertices = std::stof(aux);
	std::cout << nrVertices << std::endl;
	model = new Vertex[nrVertices];
	for (int i = 0; i < nrVertices; i++)
	{
		std::string aux;
		std::cout << i << std::endl;
		std::getline(fs, str, '[');
		std::getline(fs, str, ',');
		model[i].pos.x = std::stof(str);
		std::getline(fs, str, ',');
		model[i].pos.y = std::stof(str);
		std::getline(fs, str, ']');
		model[i].pos.z = std::stof(str);
		
		std::getline(fs, str, '[');
		std::getline(fs, str, ',');
		model[i].norm.x = std::stof(str);
		std::getline(fs, str, ',');
		model[i].norm.y = std::stof(str);
		std::getline(fs, str, ']');
		model[i].norm.z = std::stof(str);
		
		std::getline(fs, str, '[');
		std::getline(fs, str, ',');
		model[i].binorm.x = std::stof(str);
		std::getline(fs, str, ',');
		model[i].binorm.y = std::stof(str);
		std::getline(fs, str, ']');
		model[i].binorm.z = std::stof(str);
		
		std::getline(fs, str, '[');
		std::getline(fs, str, ',');
		model[i].tgt.x = std::stof(str);
		std::getline(fs, str, ',');
		model[i].tgt.y = std::stof(str);
		std::getline(fs, str, ']');
		model[i].tgt.z = std::stof(str);
		
		std::getline(fs, str, '[');
		std::getline(fs, str, ',');
		model[i].uv.x = std::stof(str);
		std::getline(fs, str, ']');
		model[i].uv.y = std::stof(str);

		std::getline(fs, str);
	}
	
	std::string numar;
	std::string tmp;

	std::getline(fs, numar);
	std::cout << numar << std::endl;
	tmp = numar.substr(11);
	nrIndices = std::stof(tmp);
	std::cout << nrIndices << std::endl;
	vIndices = new unsigned short[nrIndices];
	for (int i = 0; i < nrIndices; i++)
	{
		std::getline(fs, numar, '.');
		std::getline(fs, numar, ',');
		vIndices[i++] = std::stof(numar);
		std::getline(fs, numar, ',');
		vIndices[i++] = std::stof(numar);
		std::getline(fs, numar);
		vIndices[i] = std::stof(numar);
	}
	fs.close();
}

float alfa = 0.01;
float sens = 1;

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Pentru triunghi
	//end triunghi
	//Pentru linie
	//end linie
	//Pentru model
	glUseProgram(myModel.program);

	Matrix mod;
	mod = x.viewMatrix * x.Perspect;
	
	glBindBuffer(GL_ARRAY_BUFFER, modelId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciId);

	if (myModel.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myModel.positionAttribute);
		glVertexAttribPointer(myModel.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}


	if (myModel.matrixUniform != -1)
	{
		glUniformMatrix4fv(myModel.matrixUniform, 1, GL_FALSE, (GLfloat*)mod.m);
	}

	if (myModel.textureUniform != -1)
	{
		glBindTexture(GL_TEXTURE_2D, texturaId);//
		glUniform1i(myModel.textureUniform, 0);
	}

	if (myModel.uvAttribute != -1)
	{
		glEnableVertexAttribArray(myModel.uvAttribute);
		glVertexAttribPointer(myModel.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5*sizeof(Vector3)));
	}

	glDrawElements(GL_TRIANGLES, nrIndices, GL_UNSIGNED_SHORT, (void *)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//end model
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update ( ESContext *esContext, float deltaTime )
{
	x.setDeltaTime(deltaTime);
	POINT pct;
	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0) {
		GetCursorPos(&pct);//coord pe ecran
		ScreenToClient(esContext->hWnd, &pct);// coord in fereastra
		if (pct.x > 0 && pct.x < esContext->width / 2)
			sens = -1;
		else
			if (pct.x > esContext->width / 2 && pct.x < esContext->width)
				sens = 1;
	}
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

