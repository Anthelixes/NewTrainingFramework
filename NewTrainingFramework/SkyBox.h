#pragma once
#include "SceneObject.h"

class SkyBox: public SceneObject
{
	float	offsetY;
public:
	void	Draw();
	void	Update();
	SkyBox();
	SkyBox(float);
	~SkyBox();
};

