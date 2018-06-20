#include "stdafx.h"
#include "ResourceManager.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "../Resources/rapidxml-1.13/rapidxml.hpp"

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
	for (xml_node<> * modelNode = root_node->first_node("models"); modelNode; modelNode = modelNode->next_sibling()) {
		for (xml_node<> * childNode = modelNode->first_node("model"); childNode; childNode = childNode->next_sibling())
		{
			cout << "\t  models\tid" << childNode->first_attribute("id")->value();
			cout << "\t  \t  \tpath \t" << childNode->first_node("path")->value();
			cout << '\n';
		}
	}
	for (xml_node<> * modelNode = root_node->first_node("shaders"); modelNode; modelNode = modelNode->next_sibling()) {
		for (xml_node<> * childNode = modelNode->first_node("shader"); childNode; childNode = childNode->next_sibling())
		{
			cout << "\t  shaders\tid" << childNode->first_attribute("id")->value();
			cout << "\t  \t vs \t" << childNode->first_node("vs")->value();
			cout << "\t  \t fs \t" << childNode->first_node("fs")->value();
			cout << '\n';
		}
	}
	for (xml_node<> * modelNode = root_node->first_node("textures"); modelNode; modelNode = modelNode->next_sibling()) {
		for (xml_node<> * childNode = modelNode->first_node("texture"); childNode; childNode = childNode->next_sibling())
		{
			cout << "\t  textures\tid" << childNode->first_attribute("id")->value();
			cout << "\t type" << childNode->first_attribute("type")->value();
			cout << "\t  \t  \tpath \t" << childNode->first_node("path")->value();
			cout << "\t  \t min_filter \t" << childNode->first_node("min_filter")->value();
			cout << "\t  \t mag_filter \t" << childNode->first_node("mag_filter")->value();
			cout << "\t  \t wrap_s \t" << childNode->first_node("wrap_s")->value();
			cout << "\t  \t wrap_t \t" << childNode->first_node("wrap_t")->value();
			cout << '\n';
		}
	}
	theFile.close();
}

ResourceManager* ResourceManager::getInstance()
{
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
