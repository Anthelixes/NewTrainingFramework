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
	Vector3	color;
	Vector3	lightType;
	Vector3	diffDirection;
	Vector3	diffPosition;
	Vector3	diffColor;
	Vector3	specColor;
	Vector3 ambientalColor;
	Vector3	spotLightPosition; //
	Vector3	spotLightDirection; //?????
	float	spotLightOpening; //
	float	specPower;
	float	ratio;
	float	r, R;
	bool	debug;

	void	Init();
	void	Draw();
	void	Update();
	Camera*	getActiveCamera();
	static SceneManager* getInstance();
	~SceneManager();
};