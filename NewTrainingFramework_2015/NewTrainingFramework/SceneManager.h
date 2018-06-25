#pragma once
#include <vector>
#include <map>
#include "Camera.h"
#include "SceneObject.h"

class SceneManager
{
private:
	
	static SceneManager* spInstance;
	std::map<unsigned int, SceneObject*>	sceneObject;
	std::map<unsigned int, Camera*>			camera;
	Vector3	backgroundColor;
	unsigned int	activeCamera;
	SceneManager();
public:
	bool				debug;
	void	Init();
	void	Draw();
	void	Update();
	Camera*	getActiveCamera();
	static SceneManager* getInstance();
	~SceneManager();

	void metodaInstanta();
	void freeResource();
};