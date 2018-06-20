#include "stdafx.h"
#include "Model.h"
#include <string>


Model::Model()
{
}

void Model::Load() {
	std::ifstream fs;
	fs.open("../" + mr->mr);
	if (!fs)
		std::cout << "Unable to open\n" << std::endl;
	std::string str;
	std::string aux;
	std::getline(fs, str);
	std::cout << str << std::endl;
	aux = str.substr(12);
	nrVertices = std::stof(aux);
	std::cout << nrVertices << std::endl;
	vVertices = new Vertex[nrVertices];
	for (int i = 0; i < nrVertices; i++)
	{
		std::string aux;
		std::cout << i << std::endl;
		std::getline(fs, str, '[');
		std::getline(fs, str, ',');
		vVertices[i].pos.x = std::stof(str);
		std::getline(fs, str, ',');
		vVertices[i].pos.y = std::stof(str);
		std::getline(fs, str, ']');
		vVertices[i].pos.z = std::stof(str);

		std::getline(fs, str, '[');
		std::getline(fs, str, ',');
		vVertices[i].norm.x = std::stof(str);
		std::getline(fs, str, ',');
		vVertices[i].norm.y = std::stof(str);
		std::getline(fs, str, ']');
		vVertices[i].norm.z = std::stof(str);

		std::getline(fs, str, '[');
		std::getline(fs, str, ',');
		vVertices[i].binorm.x = std::stof(str);
		std::getline(fs, str, ',');
		vVertices[i].binorm.y = std::stof(str);
		std::getline(fs, str, ']');
		vVertices[i].binorm.z = std::stof(str);

		std::getline(fs, str, '[');
		std::getline(fs, str, ',');
		vVertices[i].tgt.x = std::stof(str);
		std::getline(fs, str, ',');
		vVertices[i].tgt.y = std::stof(str);
		std::getline(fs, str, ']');
		vVertices[i].tgt.z = std::stof(str);

		std::getline(fs, str, '[');
		std::getline(fs, str, ',');
		vVertices[i].uv.x = std::stof(str);
		std::getline(fs, str, ']');
		vVertices[i].uv.y = std::stof(str);

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
	//
	nrIndici = nrIndices;
	nrIndiciWired = sizeof(vIndices) / sizeof(*vIndices);
	std::cout << nrIndiciWired << std::endl;
	vboId = nrVertices;
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, nrVertices * sizeof(Vertex), vVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndices * sizeof(unsigned short), vIndices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Model::setModelResource(ModelResource *modelResource) {
	mr = modelResource;
}

GLuint Model::getIboId() {
	return iboId;
}

int Model::getNrInd() {
	return nrIndici;
}

int Model::getNrIndW() {
	return nrIndiciWired;
}

GLuint Model::getVboId() {
	return vboId;
}

GLuint Model::getWIboId() {
	return wiredIboId;
}

Model::~Model()
{
}
