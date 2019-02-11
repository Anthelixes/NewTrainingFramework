#include "stdafx.h"
#include "../Resources/rapidxml-1.13/rapidxml.hpp"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Terrain.h"
#include "Fire.h"
#include "SkyBox.h"
#include "../Utilities/utilities.h"


using namespace rapidxml;
using namespace std;

extern Camera cam;

SceneManager* SceneManager::spInstance = NULL;

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
			}
			else if ((strcmp(childNode->first_node("type")->value(), "terrain")) == 0) {
				Terrain *terrain = new Terrain(atoi(childNode->first_node("cells")->value()),
					(float)atof(childNode->first_node("dimensiune")->value()),
					(float)atof(childNode->first_node("offsetY")->value()), 
					childNode->first_node("model")->value());

				terrain->setHeight(Vector3(atof(childNode->first_node("inaltimi")->first_node("r")->value()),
					atof(childNode->first_node("inaltimi")->first_node("g")->value()),
					atof(childNode->first_node("inaltimi")->first_node("b")->value())));
				scene = (SceneObject*)terrain;
			}
			else if ((strcmp(childNode->first_node("type")->value(), "Fire")) == 0) {
				scene = new Fire(atof(childNode->first_node("dispMax")->value()));
			}
			else if ((strcmp(childNode->first_node("type")->value(), "SkyBox")) == 0) {
				SkyBox *skybox = new SkyBox((float)atof(childNode->first_node("offsetY")->value()));
				scene = (SceneObject*)skybox;
			}

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
		
	}
	xml_node<> * lmodelNode = root_node->first_node("ambientalLight");
	ambientalColor = Vector3(atof(lmodelNode->first_node("color")->first_node("r")->value()),
		atof(lmodelNode->first_node("color")->first_node("g")->value()),
		atof(lmodelNode->first_node("color")->first_node("b")->value()));
	ratio = atof(lmodelNode->first_node("ratio")->value());
	
	for (xml_node<> * modelNode = root_node->first_node("lights"); modelNode; modelNode = modelNode->next_sibling()) {
		for (xml_node<> * childNode = modelNode->first_node("light"); childNode; childNode = childNode->next_sibling())
		{
			if (strcmp(childNode->first_attribute("type")->value(), "Directional") == 0) {
				lightType.y = 1.0;
				diffColor = Vector3(atof(childNode->first_node("diffuseColor")->first_node("color")->first_node("r")->value()),
					atof(childNode->first_node("diffuseColor")->first_node("color")->first_node("g")->value()),
					atof(childNode->first_node("diffuseColor")->first_node("color")->first_node("b")->value()));
				diffDirection = Vector3(atof(childNode->first_node("diffuseColor")->first_node("direction")->first_node("x")->value()),
					atof(childNode->first_node("diffuseColor")->first_node("direction")->first_node("y")->value()),
					atof(childNode->first_node("diffuseColor")->first_node("direction")->first_node("z")->value()));
				specColor = Vector3(atof(childNode->first_node("specularColor")->first_node("color")->first_node("r")->value()),
					atof(childNode->first_node("specularColor")->first_node("color")->first_node("g")->value()),
					atof(childNode->first_node("specularColor")->first_node("color")->first_node("b")->value()));
				specPower = atof(childNode->first_node("specularColor")->first_node("specPower")->value());
			}
			else if (strcmp(childNode->first_attribute("type")->value(), "Point") == 0) {
				lightType.z = 1.0;
				diffColor = Vector3(atof(childNode->first_node("diffuseColor")->first_node("color")->first_node("r")->value()),
					atof(childNode->first_node("diffuseColor")->first_node("color")->first_node("g")->value()),
					atof(childNode->first_node("diffuseColor")->first_node("color")->first_node("b")->value()));
				diffPosition = Vector3(atof(childNode->first_node("diffuseColor")->first_node("direction")->first_node("x")->value()),
					atof(childNode->first_node("diffuseColor")->first_node("direction")->first_node("y")->value()),
					atof(childNode->first_node("diffuseColor")->first_node("direction")->first_node("z")->value()));
				specColor = Vector3(atof(childNode->first_node("specularColor")->first_node("color")->first_node("r")->value()),
					atof(childNode->first_node("specularColor")->first_node("color")->first_node("g")->value()),
					atof(childNode->first_node("specularColor")->first_node("color")->first_node("b")->value()));
				specPower = atof(childNode->first_node("specularColor")->first_node("specPower")->value());
			}
			else if (strcmp(childNode->first_attribute("type")->value(), "Spotlight") == 0) {
				lightType.x = 1.0;
				diffColor = Vector3(atof(childNode->first_node("diffuseColor")->first_node("color")->first_node("r")->value()),
					atof(childNode->first_node("diffuseColor")->first_node("color")->first_node("g")->value()),
					atof(childNode->first_node("diffuseColor")->first_node("color")->first_node("b")->value()));
				diffDirection = Vector3(atof(childNode->first_node("diffuseColor")->first_node("direction")->first_node("x")->value()),
					atof(childNode->first_node("diffuseColor")->first_node("direction")->first_node("y")->value()),
					atof(childNode->first_node("diffuseColor")->first_node("direction")->first_node("z")->value()));
				specColor = Vector3(atof(childNode->first_node("specularColor")->first_node("color")->first_node("r")->value()),
					atof(childNode->first_node("specularColor")->first_node("color")->first_node("g")->value()),
					atof(childNode->first_node("specularColor")->first_node("color")->first_node("b")->value()));
				specPower = atof(childNode->first_node("specularColor")->first_node("specPower")->value());

				spotLightPosition = Vector3(atof(childNode->first_node("position")->first_node("x")->value()),
					atof(childNode->first_node("position")->first_node("y")->value()),
					atof(childNode->first_node("position")->first_node("z")->value()));
				spotLightOpening = atof(childNode->first_node("deschidere")->value());
				spotLightDirection = Vector3(atof(childNode->first_node("direction")->first_node("x")->value()),
					atof(childNode->first_node("direction")->first_node("y")->value()),
					atof(childNode->first_node("direction")->first_node("z")->value()));
			}
		}
	}

	xml_node<> *modelNode = root_node->first_node("fog");
	color = Vector3(atof(modelNode->first_node("color")->first_node("r")->value()),
		atof(modelNode->first_node("color")->first_node("g")->value()),
		atof(modelNode->first_node("color")->first_node("b")->value()));
	r = atof(modelNode->first_node("raza_mica")->value());
	R = atof(modelNode->first_node("raza_mare")->value());
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
	for (std::map<unsigned int, SceneObject*>::iterator it = sceneObject.begin(); it != sceneObject.end(); ++it)
		it->second->Update();
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
