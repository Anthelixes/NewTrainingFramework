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
#include "../Utilities/esUtil.h"
#include "ResourceManager.h"
#include "SceneManager.h"



//Camera			x;
GLuint			vboId;
GLuint			lineId;
GLuint			texturaId; //pt textura
GLuint			modelId; //pt vertecsi
GLuint			indiciId; //pt indici
GLuint			wiredIboId; //pt wired
Shaders			myShaders; //pt triunghi
Shaders			lineShaders; //pt linie
Shaders			myModel; //pt model
Vertex*			model; //vector de vertecsi
int				nrVertices;
int				nrIndices;
int				nrIndicesW;
unsigned short*	vIndices;
unsigned short* wIndices;
std::vector<unsigned int>	indices;
std::vector<unsigned int>   windices;
void			parsare();
bool			wired = true;

char*	array_pixels;
GLint	width, height, bpp;
GLuint	format;

ResourceManager* rm = ResourceManager::getInstance();
SceneManager*	sm = SceneManager::getInstance();

int Init ( ESContext *esContext )
{
	glEnable(GL_DEPTH_TEST);
	ResourceManager::getInstance()->Init();
	SceneManager::getInstance()->Init();
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	//triangle data (heap)
	
	//parsare();


	//buffer object
	
	//pentru model
	/*(1, &modelId);
	glBindBuffer(GL_ARRAY_BUFFER, modelId);
	glBufferData(GL_ARRAY_BUFFER, nrVertices*sizeof(Vertex), model, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (!wired) {
		glGenBuffers(1, &indiciId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndices * sizeof(unsigned short), vIndices, GL_STATIC_DRAW); //
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else
	{
		glGenBuffers(1, &wiredIboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wiredIboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, windices.size() * sizeof(unsigned int), &(windices)[0], GL_STATIC_DRAW);//&(windices)[0]
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}*/

	//end model

	/*
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
	glBindTexture(GL_TEXTURE_2D, 0);*/

	//creation of shaders and program 
	/*myModel.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	lineShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");*/

	return 0;
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

	/*
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
	
	*/

	std::string		aux1;
	unsigned int	ind1, ind;
	float			vertex;

	std::getline(fs, numar);
	std::cout << numar << std::endl;
	tmp = numar.substr(11);
	nrIndices = std::stof(tmp);
	std::cout << nrIndices << std::endl;

	nrIndicesW = nrIndices / 3;
	std::cout << nrIndicesW << std::endl;
	vIndices = new unsigned short[nrIndices];
	wIndices = new unsigned	short[nrIndices / 3];

	for (int i = 0; i < nrIndices / 3; i++)
	{
		fs >> aux1;
		fs >> aux1;
		ind = atoi(aux1.c_str());
		ind1 = ind;
		indices.push_back(ind);
		windices.push_back(ind);
		fs >> aux1;
		ind = atoi(aux1.c_str());
		indices.push_back(ind);
		windices.push_back(ind);
		windices.push_back(ind);
		fs >> aux1;
		ind = atoi(aux1.c_str());
		windices.push_back(ind);
		windices.push_back(ind);
		windices.push_back(ind1);
		indices.push_back(ind);
	}
	nrIndicesW = nrIndices / 3;
	for (int i = 0; i < nrIndices; i++)
	{
		vIndices[i] = indices[i];
	}
	for (int i = 0; i < nrIndicesW; i++)
	{
		wIndices[i] = windices.at(i);
	}

	/*
	for (int i = 0; i < nrIndices / 3; i++)
	{
		std::getline(fs, numar, '.');
		std::getline(fs, numar, ',');
		vIndices[i] = std::stof(numar);
		wIndices[i] = std::stof(numar);
		std::cout << wIndices[i] << "\t" << vIndices << std::endl;
		i++;

		std::getline(fs, numar, ',');
		vIndices[i] = std::stof(numar);
		wIndices[i] = std::stof(numar);
		wIndices[i] = std::stof(numar);
		std::cout << wIndices[i] << wIndices[i+1] << "\t" << vIndices << std::endl;
		i++;

		std::getline(fs, numar);
		wIndices[i] = std::stof(numar);
		wIndices[i] = std::stof(numar);
		wIndices[i] = std::stof(numar);
		vIndices[i] = std::stof(numar);
		std::cout << wIndices[i] << "\t" << wIndices[i + 1] << "\t" << wIndices[i+2] << "\t" << vIndices << std::endl;
	}*/
	fs.close();
}

float alfa = 0.01;
float sens = 1;

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	SceneManager::getInstance()->Draw();
	/*
	glUseProgram(myModel.program);

	Matrix mod;
	mod = x.viewMatrix * x.Perspect;
	
	glBindBuffer(GL_ARRAY_BUFFER, modelId);
	if (!wired)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiciId);
	else
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wiredIboId);

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

	if(!wired)
		glDrawElements(GL_TRIANGLES, nrIndices, GL_UNSIGNED_SHORT, (void *)0);
	
	else
		glDrawElements(GL_LINES, nrIndices*2, GL_UNSIGNED_INT, (void *)0);//
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (!wired)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	else
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//

	//end model*/
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update ( ESContext *esContext, float deltaTime )
{
	Camera *x = SceneManager::getInstance()->getActiveCamera();
	x->setDeltaTime(deltaTime);
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
	Camera *x = SceneManager::getInstance()->getActiveCamera();
	switch (key)
	{
	case 'W':
		x->moveOz(-1);
		break;
	case 'S':
		x->moveOz(1);
		break;
	case 'Q':
		x->moveOy(1);
		break;
	case 'E':
		x->moveOy(-1);
		break;
	case 'A':
		x->moveOx(1);
		break;
	case 'D':
		x->moveOx(-1);
		break;
	case 'I':
		x->rotateOx(1);
		break;
	case 'L':
		x->rotateOy(-1);
		break;
	case 'K':
		x->rotateOx(-1);
		break;
	case 'J':
		x->rotateOy(1);
		break;
	case 'U':
		x->rotateOz(1);
		break;
	case 'O':
		x->rotateOz(-1);
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

