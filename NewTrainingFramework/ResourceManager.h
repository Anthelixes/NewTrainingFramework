#pragma once
#include <map>
#include <vector>
#include "ModelResource.h"
#include "ShaderResource.h"
#include "TextureResource.h"
#include "Model.h"
#include "Texture.h"
#include "Shader.h"

class ResourceManager
{
private:
	ResourceManager();
	std::map<unsigned int, Model*>				procesareModel;
	std::map<unsigned int, Texture*>			procesareTexture;
	std::map<unsigned int, Shader*>				procesareShader;
	std::map<unsigned int, ModelResource*>		model;
	std::map<unsigned int, TextureResource*>	texture;
	std::map<unsigned int, ShaderResource*>		shader;
	static ResourceManager *spInstance;
public:
	void					Init();
	static ResourceManager*	getInstance();
	Model*		loadModel(unsigned int);
	Texture*	loadTexture(unsigned int);
	Shader*		loadShader(unsigned int);
	~ResourceManager();

	void metodaInstanta();
	void freeResources();
};