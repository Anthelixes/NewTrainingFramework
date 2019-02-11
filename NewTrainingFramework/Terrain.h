#pragma once
#include "SceneObject.h"


class Terrain: public SceneObject
{
	std::string	model_terrain;
	int			nr_celule;
	float		dim_celula;
	float		offsetY;
	Vector3		centru;
	Vector3		height;
public:
	void	setHeight(Vector3);
	void	Draw();
	void	Update();
	Terrain();
	Terrain(int, float, float, std::string);
	~Terrain();
};

