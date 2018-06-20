#pragma once
#include "ModelResource.h"
#include "Vertex.h"
#include <vector>
#include "../Utilities/utilities.h"
class Model
{
private:
	ModelResource * mr;
	int	nrIndici;
	int	nrIndiciWired;
	GLuint	iboId;
	GLuint	wiredIboId;
	GLuint	vboId;
public:
	int				nrVertices; //nr vertexi
	int				nrIndices; //nr indici
	unsigned short*	vIndices; //vector de indici
	Vertex*			vVertices; //vector de vertecsi
	void	Load();
	GLuint	getIboId();
	GLuint	getWIboId();
	GLuint	getVboId();
	int		getNrInd();
	int		getNrIndW();
	void	setModelResource(ModelResource*);
	Model();
	~Model();
};