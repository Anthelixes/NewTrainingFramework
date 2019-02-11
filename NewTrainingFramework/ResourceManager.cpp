#include "stdafx.h"
#include "../Resources/rapidxml-1.13/rapidxml.hpp"
#include "ResourceManager.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include "../Utilities/utilities.h"

using namespace rapidxml;
using namespace std;

ResourceManager* ResourceManager::spInstance = NULL;

ResourceManager::ResourceManager()
{
}

void ResourceManager::Init() {
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile("../Resources/resourceManager/resourceManager.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("resourceManager");
	// Iterate over the brewerys
	//root_node = root_node->first_node("models");
	for (xml_node<> * modelNode = root_node->first_node("models"); modelNode; modelNode = modelNode->next_sibling()){
		for (xml_node<> * childNode = modelNode->first_node("model"); childNode; childNode = childNode->next_sibling())
		{
			ModelResource *mr = new ModelResource{
				childNode->first_node("path")->value()
			};
			unsigned int id = atoi(childNode->first_attribute("id")->value());
			model.insert(pair <unsigned int, ModelResource*>(id, mr));
		}
	}
	for (xml_node<> * modelNode = root_node->first_node("shaders"); modelNode; modelNode = modelNode->next_sibling()) {
		for (xml_node<> * childNode = modelNode->first_node("shader"); childNode; childNode = childNode->next_sibling())
		{
			ShaderResource *sr = new ShaderResource{
				childNode->first_node("vs")->value(), childNode->first_node("fs")->value()
			};
			unsigned int id = atoi(childNode->first_attribute("id")->value());
			shader.insert(pair<unsigned int, ShaderResource*>(id, sr));
		}
	}
	for (xml_node<> * modelNode = root_node->first_node("textures"); modelNode; modelNode = modelNode->next_sibling()) {
		for (xml_node<> * childNode = modelNode->first_node("texture"); childNode; childNode = childNode->next_sibling())
		{
			TextureResource *tr = new TextureResource{
				childNode->first_attribute("type")->value(),
				childNode->first_node("path")->value(),
				childNode->first_node("min_filter")->value(),
				childNode->first_node("mag_filter")->value(),
				childNode->first_node("wrap_s")->value(),
				childNode->first_node("wrap_t")->value()
			};

			unsigned int id = atoi(childNode->first_attribute("id")->value());
			texture.insert(pair<unsigned int, TextureResource*>(id, tr));
		}
	}
	theFile.close();
}

Model* ResourceManager::loadModel(unsigned int id) {
	std::map<unsigned int, Model*>::iterator it;
	it = procesareModel.find(id);
	if (it != procesareModel.end())
		return it->second; //mi-a gasit resursa in vect. returneaza point catre resursa incarcata
	else {
		//trebuie sa creeze o resursa de acel tip
		//se apeleaza Load() pentru ea
		//e adaugata in vectorul de resurse si e returnat un pointer catre ea
		Model *m = new Model();
		std::map<unsigned int, ModelResource*>::iterator it2;
		it2 = model.find(id);
		
		m->setModelResource(it2->second);
		m->Load();
		procesareModel.insert(pair<unsigned int, Model*>(id, m));
		return m;
	}
}

Texture* ResourceManager::loadTexture(unsigned int id) {
	std::map<unsigned int, Texture*>::iterator it;

	it = procesareTexture.find(id);
	if (it != procesareTexture.end())
		return it->second; //mi-a gasit resursa in vect. returneaza point catre resursa incarcata
	else {
		//trebuie sa creeze o resursa de acel tip
		//se apeleaza Load() pentru ea
		//e adaugata in vectorul de resurse si e returnat un pointer catre ea
		Texture *m = new Texture();
		std::map<unsigned int, TextureResource*>::iterator it2 = texture.find(id);
		m->setTextureResource(it2->second);
		m->Load();
		procesareTexture.insert(pair<unsigned int, Texture*>(id, m));
		return m;
	}
}

Shader* ResourceManager::loadShader(unsigned int id) {
	std::map<unsigned int, Shader*>::iterator it;

	it = procesareShader.find(id);
	if (it != procesareShader.end())
		return it->second; //mi-a gasit resursa in vect. returneaza point catre resursa incarcata
	else {
		//trebuie sa creeze o resursa de acel tip
		//se apeleaza Load() pentru ea
		//e adaugata in vectorul de resurse si e returnat un pointer catre ea
		Shader *m = new Shader();
		std::map<unsigned int, ShaderResource*>::iterator it2 = shader.find(id);
		m->setShaderResource(it2->second);
		m->Load();
		procesareShader.insert(pair<unsigned int, Shader*>(id, m));
		return m;
	}
}

ResourceManager* ResourceManager::getInstance() {
	if (!spInstance)
	{
		spInstance = new ResourceManager();
	}
	return spInstance;
}

ResourceManager::~ResourceManager()
{
	spInstance = NULL;
}