#pragma once
#include "SceneObject.h"

extern float uTime;

class Fire: public SceneObject	
{
	float dispMax;

public:
	Fire();
	Fire(float);
	void Draw();
	void Update();
	~Fire();
};

