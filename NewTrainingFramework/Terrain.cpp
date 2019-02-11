#include "stdafx.h"
#include "Terrain.h"
#include "Camera.h"
#include "SceneManager.h"

Terrain::Terrain()
{
}


Terrain::Terrain(int nr_celule, float dim_celula, float offsetY, std::string model_terrain) {
	this->nr_celule = nr_celule;
	this->dim_celula = dim_celula;
	this->offsetY = offsetY;
	this->model_terrain = model_terrain;

	Camera cam;

	centru = cam.getPos();

	
	if (model_terrain == "generated") {
		model = new Model();

		for (int i = 0; i < nr_celule + 1; i++)
			for (int j = 0; j < nr_celule + 1; j++)
			{
				Vertex *v = new Vertex();
				v->pos = Vector3(- nr_celule / 2 * dim_celula + i*dim_celula, offsetY, - nr_celule /2 * dim_celula + j * dim_celula);
				v->norm = Vector3(0.0f, 1.0f, 0.0f);
				v->binorm = Vector3(0.0f, 1.0f, 0.0f);
				v->tgt = Vector3(0.0f, 1.0f, 0.0f);
				v->uv = Vector2(i, j);
				v->uv_blend = Vector2(i / (GLfloat) nr_celule, j / (GLfloat) nr_celule);
				model->points.push_back(*v);
			}
		
		for (unsigned int i = 0; i < nr_celule; i++)
			for (unsigned int j = 0; j < nr_celule; j++)
			{
				model->vIndices.push_back(i*(nr_celule + 1) + j);
				model->vIndices.push_back((i + 1) * (nr_celule + 1) + j);
				model->vIndices.push_back(i * (nr_celule + 1) + j + 1);
				model->vIndices.push_back(i * (nr_celule + 1) + j + 1);
				model->vIndices.push_back((i + 1) * (nr_celule + 1) + j);
				model->vIndices.push_back((i + 1) * (nr_celule + 1) + j + 1);
			}
		}
	model->nrVertex = model->points.size();
	model->nrIndices = model->vIndices.size();

	glGenBuffers(1, &model->vboId);
	glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
	glBufferData(GL_ARRAY_BUFFER, model->getNrVertex() * sizeof(Vertex), &(model->points)[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &model->iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->getNrInd() * sizeof(unsigned short), &(model->vIndices)[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
}

void Terrain::Update() {

	SceneObject::Update();
	Camera *x;
	x = SceneManager::getInstance()->getActiveCamera();
	
	if (abs(x->getPos().z - centru.z) > dim_celula && x->getPos().z > centru.z)
	{
		for (int i = 0; i < model->points.size(); i++)
		{
			model->points[i].pos.z += dim_celula;
			model->points[i].uv_blend.y += 1.0 / nr_celule;
		}
		centru.z += dim_celula;
	}
	else if (abs(x->getPos().z - centru.z) > dim_celula && x->getPos().z < centru.z)
	{
		for (int i = 0; i < model->points.size(); i++)
		{
			model->points[i].pos.z -= dim_celula;
			model->points[i].uv_blend.y -= 1.0 / nr_celule;
		}
		centru.z -= dim_celula;
	}

	if (abs(x->getPos().x - centru.x) > dim_celula && x->getPos().x > centru.x)
	{
		for (int i = 0; i < model->points.size(); i++)
		{
			model->points[i].pos.x += dim_celula;
			model->points[i].uv_blend.x += 1.0 / nr_celule;
		}
		centru.x += dim_celula;
	}
	else if (abs(x->getPos().x - centru.x) > dim_celula && x->getPos().x < centru.x)
	{
		for (int i = 0; i < model->points.size(); i++)
		{
			model->points[i].pos.x -= dim_celula;
			model->points[i].uv_blend.x -= 1.0 / nr_celule;
		}
		centru.x -= dim_celula;
	}

	
	glBindBuffer(GL_ARRAY_BUFFER, model->vboId);
	glBufferData(GL_ARRAY_BUFFER, model->points.size() * sizeof(Vertex), model->points.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Terrain::Draw() {
	glUseProgram(shader->getId());

	Camera *x;
	x = SceneManager::getInstance()->getActiveCamera();

	glBindBuffer(GL_ARRAY_BUFFER, model->getVboId());
	if (!SceneManager::getInstance()->debug)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getIboId());
	else
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getWIboId());

	if (shader->heightUniform != -1)
	{
		glUniform3f(shader->heightUniform, height.x, height.y, height.z);
	}

	SceneObject::SendCommonData();

	if (!SceneManager::getInstance()->debug)
		glDrawElements(GL_TRIANGLES, model->getNrInd(), GL_UNSIGNED_SHORT, (void *)0);

	else
		glDrawElements(GL_LINES, model->getNrInd() * 2, GL_UNSIGNED_SHORT, (void *)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Terrain::setHeight(Vector3 height) {
	this->height = height;
}

Terrain::~Terrain()
{
}
