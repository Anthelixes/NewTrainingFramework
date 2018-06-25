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

	//Matrix mod;
	Camera *x;
	x = SceneManager::getInstance()->getActiveCamera();

	
	glBindBuffer(GL_ARRAY_BUFFER, model->getVboId());//modelId
	if (!SceneManager::getInstance()->debug)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getIboId());//indiciId
	else
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getWIboId());
	
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

	if (!SceneManager::getInstance()->debug)
		glDrawElements(GL_TRIANGLES, model->getNrInd(), GL_UNSIGNED_SHORT, (void *)0);

	else
		glDrawElements(GL_LINES, model->getNrInd() * 2, GL_UNSIGNED_SHORT, (void *)0);//

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
