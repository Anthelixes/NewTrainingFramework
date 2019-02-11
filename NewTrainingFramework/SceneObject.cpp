#include "stdafx.h"
#include "SceneObject.h"
#include "SceneManager.h"
#include "Globals.h"
#include "Camera.h"
#include "../Utilities/utilities.h"


SceneObject::SceneObject()
{
}

SceneObject::SceneObject(Vector3 position, Vector3 rotation, Vector3 scale, bool depthTest){
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	this->depthTest = depthTest;
}

void SceneObject::setModel(Model *model) {
	this->model = model;
}

void SceneObject::setShader(Shader *shader) {
	this->shader = shader;
}

void SceneObject::addTextures(Texture* t) {
	textures.push_back(t);
}

void SceneObject::Draw() {
	glUseProgram(shader->getId());
	
	glBindBuffer(GL_ARRAY_BUFFER, model->getVboId());
	if (!SceneManager::getInstance()->debug)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getIboId());
	else
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getWIboId());
	
	SceneObject::SendCommonData();

	if (!SceneManager::getInstance()->debug)
		glDrawElements(GL_TRIANGLES, model->getNrInd(), GL_UNSIGNED_SHORT, (void *)0);

	else
		glDrawElements(GL_LINES, model->getNrInd() * 2, GL_UNSIGNED_SHORT, (void *)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SceneObject::SendCommonData() {

	Camera *x;
	x = SceneManager::getInstance()->getActiveCamera();

	if (shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(shader->positionAttribute);
		glVertexAttribPointer(shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}


	if (shader->matrixUniform != -1)
	{
		glUniformMatrix4fv(shader->matrixUniform, 1, GL_FALSE, (GLfloat*)mvp.m);
	}

	for (int i = 0; i < textures.size(); i++)
	{
		if (shader->textureUniform[i] != -1)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures.at(i)->getId());
			glUniform1i(shader->textureUniform[i], i);
		}
	}

	if (shader->skyboxUniform != -1)
	{
		for (int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_CUBE_MAP, textures.at(i)->getId());
			glUniform1i(shader->skyboxUniform, i);
		}
	}

	if (shader->uvAttribute != -1)
	{
		glEnableVertexAttribArray(shader->uvAttribute);
		glVertexAttribPointer(shader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(Vector3)));
	}

	if (shader->uvblendAttribute != -1)
	{
		glEnableVertexAttribArray(shader->uvblendAttribute);
		glVertexAttribPointer(shader->uvblendAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(Vector3) + sizeof(Vector2)));
	}

	if (shader->rUniform != -1)
	{
		glUniform1f(shader->rUniform, SceneManager::getInstance()->r);
	}

	if (shader->RUniform != -1)
	{
		glUniform1f(shader->RUniform, SceneManager::getInstance()->R);
	}

	if (shader->camUniform != -1)
	{
		glUniform3f(shader->camUniform, x->getPos().x, x->getPos().y, x->getPos().z);
	}

	Matrix p;
	p.SetScale(scale);
	p = p * m.SetRotationX(rotation.x);
	p = p * m.SetRotationY(rotation.y);
	p = p * m.SetRotationZ(rotation.z);
	p = p * m.SetTranslation(position);
	m = p;

	if (shader->worldUniform != -1)
	{
		glUniformMatrix4fv(shader->worldUniform, 1, GL_FALSE, (GLfloat *)m.m);
	}

	if (shader->ambUniform != -1)
	{
		glUniform3f(shader->ambUniform, SceneManager::getInstance()->ambientalColor.x, SceneManager::getInstance()->ambientalColor.y, SceneManager::getInstance()->ambientalColor.z);
	}

	if (shader->normAttribute != -1)
	{
		glEnableVertexAttribArray(shader->normAttribute);
		glVertexAttribPointer(shader->normAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(2*sizeof(Vector3)));
	}

	if (shader->diffColorUniform != -1)
	{
		glUniform3f(shader->diffColorUniform, SceneManager::getInstance()->diffColor.x, SceneManager::getInstance()->diffColor.y, SceneManager::getInstance()->diffColor.z);
	}

	if (shader->specColorUniform != -1)
	{
		glUniform3f(shader->specColorUniform, SceneManager::getInstance()->specColor.x, SceneManager::getInstance()->specColor.y, SceneManager::getInstance()->specColor.z);
	}
	if (shader->diffDirectionUniform != -1)
	{
		glUniform3f(shader->diffDirectionUniform, SceneManager::getInstance()->diffDirection.x, SceneManager::getInstance()->diffDirection.y, SceneManager::getInstance()->diffDirection.z);
	}
	if (shader->diffPositionUniform != -1)
	{
		glUniform3f(shader->diffPositionUniform, SceneManager::getInstance()->diffPosition.x, SceneManager::getInstance()->diffPosition.y, SceneManager::getInstance()->diffPosition.z);
	}
	if (shader->ratioUniform != -1)
	{
		glUniform1f(shader->ratioUniform, SceneManager::getInstance()->ratio);
	}
	if (shader->specPowerUniform != -1)
	{
		glUniform1f(shader->specPowerUniform, SceneManager::getInstance()->specPower);
	}
	if (shader->lightTypeUniform != -1)
	{
		glUniform3f(shader->lightTypeUniform, SceneManager::getInstance()->lightType.x, SceneManager::getInstance()->lightType.y, SceneManager::getInstance()->lightType.z);
	}
	if (shader->spotLightPositionUniform != -1)
	{
		glUniform3f(shader->spotLightPositionUniform, SceneManager::getInstance()->spotLightPosition.x, SceneManager::getInstance()->spotLightPosition.y, SceneManager::getInstance()->spotLightPosition.z);
	}
	if (shader->spotLightOpeningUniform != -1)
	{
		glUniform1f(shader->spotLightOpeningUniform, SceneManager::getInstance()->spotLightOpening);
	}
	if (shader->spotLightDirectionUniform != -1)
	{
		glUniform3f(shader->spotLightDirectionUniform, SceneManager::getInstance()->spotLightDirection.x, SceneManager::getInstance()->spotLightDirection.y, SceneManager::getInstance()->spotLightDirection.z);
	}
}

void SceneObject::Update() {

	Camera *x;
	x = SceneManager::getInstance()->getActiveCamera();

	Matrix scal, rx, ry, rz, trans, world;

	scal.SetScale(scale);
	rx.SetRotationX(rotation.x);
	ry.SetRotationY(rotation.y);
	rz.SetRotationZ(rotation.z);

	trans.SetTranslation(position);

	world = scal * rx * ry * rz * trans;
	mvp = world * x->viewMatrix * x->Perspect;
}

SceneObject::~SceneObject()
{
}
