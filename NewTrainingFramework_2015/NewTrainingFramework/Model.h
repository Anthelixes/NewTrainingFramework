#pragma once
#include "ModelResource.h"
#include "Vertex.h"
#include <vector>
#include "../Utilities/utilities.h"

class Model
{
private:
	ModelResource * mr;
	int	nrIndices;
	int	nrVertex;
	int	nrWIndices;
public:
	float	wired = true;
	GLuint	iboId;
	GLuint	wiredIboId;
	GLuint	vboId;
	std::vector<unsigned short>	vIndices;
	std::vector<unsigned short>   vWIndices;
	Vertex*						model;
	std::vector<Vertex>			points;
	void	Load();
	GLuint	getIboId();
	GLuint	getWIboId();
	GLuint	getVboId();
	int		getNrInd();
	int		getNrIndW();
	int		getNrVertex();
	void	setModelResource(ModelResource*);
	Model();
	Model(std::vector<Vertex> vert, std::vector<unsigned short> ind);
	~Model();
};