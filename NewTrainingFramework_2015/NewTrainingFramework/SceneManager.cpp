#include "stdafx.h"
#include "../Resources/rapidxml-1.13/rapidxml.hpp"
#include "ResourceManager.h"
#include "SceneManager.h"

using namespace rapidxml;
using namespace std;

extern Camera cam;

SceneManager* SceneManager::spInstance = NULL;

//IN LUCRU
void SceneManager::Init() {
	debug = false;
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile("../Resources/sceneManager/sceneManager.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("sceneManager");
	// Iterate over the brewerys
	//root_node = root_node->first_node("models");
	backgroundColor.x = atof(root_node->first_node("backgroundColor")->first_node("r")->value());
	backgroundColor.y = atof(root_node->first_node("backgroundColor")->first_node("g")->value());
	backgroundColor.z = atof(root_node->first_node("backgroundColor")->first_node("b")->value());

	for (xml_node<> * modelNode = root_node->first_node("cameras"); modelNode; modelNode = modelNode->next_sibling()) {
		for (xml_node<> * childNode = modelNode->first_node("camera"); childNode; childNode = childNode->next_sibling())
		{
			Camera *cam = new Camera{
				Vector3(atof(childNode->first_node("position")->first_node("x")->value()),
				atoi(childNode->first_node("position")->first_node("y")->value()),
				atoi(childNode->first_node("position")->first_node("z")->value())),
				Vector3(atof(childNode->first_node("target")->first_node("x")->value()),
				atoi(childNode->first_node("target")->first_node("y")->value()),
				atoi(childNode->first_node("target")->first_node("z")->value())),
				Vector3(atof(childNode->first_node("up")->first_node("x")->value()),
				atoi(childNode->first_node("up")->first_node("y")->value()),
				atoi(childNode->first_node("up")->first_node("z")->value())),
				(GLfloat)atof(childNode->first_node("translationSpeed")->value()),
				(GLfloat)atof(childNode->first_node("rotationSpeed")->value()),
				(GLfloat)atof(childNode->first_node("near")->value()),
				(GLfloat)atof(childNode->first_node("far")->value()),
				(GLfloat)atof(childNode->first_node("fov")->value())
			};
			unsigned int id = atoi(childNode->first_attribute("id")->value());
			camera.insert(pair<unsigned int, Camera*>(id, cam));
		}
	}
	activeCamera = atoi(root_node->first_node("activeCamera")->value());
	

	for (xml_node<> * modelNode = root_node->first_node("objects"); modelNode; modelNode = modelNode->next_sibling()) {
		for (xml_node<> * childNode = modelNode->first_node("object"); childNode; childNode = childNode->next_sibling())
		{
			SceneObject *scene;
			if ((strcmp(childNode->first_node("type")->value(), "normal")) == 0) {
				scene = new SceneObject();

				scene->position = Vector3(atof(childNode->first_node("position")->first_node("x")->value()),
					atof(childNode->first_node("position")->first_node("y")->value()),
					atof(childNode->first_node("position")->first_node("z")->value()));
				scene->rotation = Vector3(atof(childNode->first_node("rotation")->first_node("x")->value()),
					atof(childNode->first_node("rotation")->first_node("y")->value()),
					atof(childNode->first_node("rotation")->first_node("z")->value()));
				scene->scale = Vector3(atof(childNode->first_node("scale")->first_node("x")->value()),
					atof(childNode->first_node("scale")->first_node("y")->value()),
					atof(childNode->first_node("scale")->first_node("z")->value()));
				if (strcmp(childNode->first_node("depthTest")->value(), "true") == 0) {
					scene->depthTest = true;
				}
				else
					scene->depthTest = false;
				//cout << "selfRotateSpeed\t" << childNode->first_node("selfRotateSpeed")->value() << endl;
				//pentru followingCamera - NU MERGE

				//cout << "lights\tlight\t" << childNode->first_node("lights")->first_node("light")->value() << endl;
				//pentru position - NU MERGE

				unsigned int id = atoi(childNode->first_attribute("id")->value());

				if (strcmp(childNode->first_node("model")->value(), "generated") != 0)
					scene->setModel(ResourceManager::getInstance()->loadModel(atoi(childNode->first_node("model")->value())));

				scene->setShader(ResourceManager::getInstance()->loadShader(atoi(childNode->first_node("shader")->value())));
				std::cout << childNode->first_node("shader")->value();

				for (xml_node<> * schildNode = childNode->first_node("textures")->first_node("texture"); schildNode; schildNode = schildNode->next_sibling())
				{
					scene->addTextures(ResourceManager::getInstance()->loadTexture(atoi(schildNode->first_attribute("id")->value())));
					cout << "\t  texture\tid" << schildNode->first_attribute("id")->value() << endl;
				}

				sceneObject.insert(pair <unsigned int, SceneObject*>(id, scene));

			}
			else if ((strcmp(childNode->first_node("type")->value(), "terrain")) == 0) {
				;
			}
			//mai ramane pt type-urile speciale
			

			
		}
		
	}
	for (xml_node<> * modelNode = root_node->first_node("lights"); modelNode; modelNode = modelNode->next_sibling()) {
		for (xml_node<> * childNode = modelNode->first_node("light"); childNode; childNode = childNode->next_sibling())
		{
			//IN LUCRU
		}
	}
	theFile.close();
}

Camera*	SceneManager::getActiveCamera() {
	std::map<unsigned int, Camera*>::iterator it;
	it = camera.find(activeCamera);
	if (it != camera.end())
		return it->second;
	else {
		std::cout << "Camera nu exista";
		exit(0);
	}
}


void SceneManager::Update() {
	//
}

void SceneManager::Draw() {
	for (std::map<unsigned int, SceneObject*>::iterator it = sceneObject.begin(); it != sceneObject.end(); ++it)
		it->second->Draw();
}

SceneManager* SceneManager::getInstance()
{
	if (!spInstance)
	{
		spInstance = new SceneManager();
	}
	return spInstance;
}


SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
}
