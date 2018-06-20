#pragma once
#include <map>
#include <vector>
#include "ModelResource.h"
#include "Model.h"
#include "ShaderResource.h"
#include "Shader.h"
#include "TextureResource.h"
#include "Texture.h"

class ResourceManager
{
private:
	static ResourceManager *spInstance;
	ResourceManager();
	std::map<int, Model*>	procesareModel;
	std::map<int, Texture*>	procesareTextura;
	std::map<int, Shader*>	procesareShader;
	std::map<int, ModelResource*>	model;
	std::map<int, TextureResource*>	texture;
	std::map<int, ShaderResource*>	shader;
public:
	void static Init();
	static ResourceManager* getInstance();
	Model*		loadModel(int);
	Texture*	loadTexture(int);
	Shader*		loadShader(int);
	~ResourceManager();

	void metodaInstanta();
	void freeResources();
};

