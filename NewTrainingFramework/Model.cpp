#include "stdafx.h"
#include "Model.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "../Utilities/utilities.h"

Model::Model()
{
}

void Model::setModelResource(ModelResource *modelResource) {
	mr = modelResource;
}

Model::Model(std::vector<Vertex> vert, std::vector<unsigned short> ind)
{
	points = vert;
	vIndices = ind;
}

void Model::Load() {
	std::string		aux;
	unsigned int	ind1, ind;
	float			vertex;
	std::ifstream	f("../" + mr->path);

	if (!f)
		std::cerr << "Nu s-a gasit modelul";

	f >> aux;
	f >> aux;

	nrVertex = atoi(aux.c_str());

	for (int i = 0; i < nrVertex; i++)
	{
		points.push_back(Vertex());
		f >> aux;
		f >> aux;
		aux.erase(0, 5);
		vertex = atof(aux.c_str());

		points[i].pos.x = (GLfloat)vertex;
		f >> vertex;

		points[i].pos.y = (GLfloat)vertex;

		f >> aux;
		f >> aux;
		vertex = atof(aux.c_str());

		points[i].pos.z = (GLfloat)vertex;
		
		f >> aux;
		aux.erase(0, 6);
		vertex = atof(aux.c_str());

		points[i].norm.x = (GLfloat)vertex;

		f >> vertex;

		points[i].norm.y = (GLfloat)vertex;

		f >> aux;
		f >> aux;
		vertex = atof(aux.c_str());

		points[i].norm.z = (GLfloat)vertex;

		f >> aux;
		aux.erase(0, 8);
		vertex = atof(aux.c_str());

		points[i].binorm.x = (GLfloat)vertex;

		f >> vertex;

		points[i].binorm.y = (GLfloat)vertex;

		f >> aux;
		f >> aux;
		vertex = atof(aux.c_str());

		points[i].binorm.z = (GLfloat)vertex;


		f >> aux;
		aux.erase(0, 5);
		vertex = atof(aux.c_str());

		points[i].tgt.x = (GLfloat)vertex;

		f >> vertex;

		points[i].tgt.y = (GLfloat)vertex;

		f >> aux;
		f >> aux;
		vertex = atof(aux.c_str());

		points[i].tgt.z = (GLfloat)vertex;


		f >> aux;
		aux.erase(0, 4);
		vertex = atof(aux.c_str());

		points[i].uv.x = (GLfloat)vertex;

		f >> vertex;

		points[i].uv.y = (GLfloat)vertex;

		std::getline(f, aux);
	}

	f >> aux;
	f >> aux;
	nrIndices = atoi(aux.c_str());

	for (int i = 0; i < nrIndices / 3; i++)
	{
		f >> aux;
		f >> aux;
		ind = atoi(aux.c_str());
		ind1 = ind;
		vIndices.push_back(ind);
		vWIndices.push_back(ind);
		f >> aux;
		ind = atoi(aux.c_str());
		vIndices.push_back(ind);
		vWIndices.push_back(ind);
		vWIndices.push_back(ind);
		f >> aux;
		ind = atoi(aux.c_str());
		vWIndices.push_back(ind);
		vWIndices.push_back(ind);
		vWIndices.push_back(ind1);
		vIndices.push_back(ind);
	}

	nrWIndices = vWIndices.size();

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, nrVertex * sizeof(Vertex), &(points)[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndices * sizeof(unsigned short), &(vIndices)[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glGenBuffers(1, &wiredIboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wiredIboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vWIndices.size() * sizeof(unsigned short), &(vWIndices)[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint Model::getIboId() {
	return iboId;
}

int Model::getNrInd() {
	return nrIndices;
}

int Model::getNrIndW() {
	return nrWIndices;
}


int Model::getNrVertex() {
	return nrVertex;
}

GLuint Model::getVboId() {
	return vboId;
}

GLuint Model::getWIboId() {
	return wiredIboId;
}

Model::~Model() {
}

/*
std::ifstream fs;
fs.open("../" + mr->path);
if (!fs)
std::cout << "Unable to open\n" << std::endl;
std::string str;
std::string aux;
std::getline(fs, str);
std::cout << str << std::endl;
aux = str.substr(12);
nrVertex = std::stof(aux);
std::cout << nrVertex << std::endl;
model = new Vertex[nrVertex];
for (int i = 0; i < nrVertex; i++)
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
std::string		aux1;
unsigned int	ind1, ind;

std::getline(fs, numar);
std::cout << numar << std::endl;
tmp = numar.substr(11);
nrIndices = std::stof(tmp);
std::cout << nrIndices << std::endl;

nrWIndices = nrIndices / 3;
std::cout << nrWIndices << std::endl;

for (int i = 0; i < nrIndices / 3; i++)
{
fs >> aux1;
fs >> aux1;
ind = atoi(aux1.c_str());
ind1 = ind;
vIndices.push_back(ind);
vWIndices.push_back(ind);
fs >> aux1;
ind = atoi(aux1.c_str());
vWIndices.push_back(ind);
vWIndices.push_back(ind);
vWIndices.push_back(ind);
fs >> aux1;
ind = atoi(aux1.c_str());
vWIndices.push_back(ind);
vWIndices.push_back(ind);
vWIndices.push_back(ind1);
vIndices.push_back(ind);
}
fs.close();
*/