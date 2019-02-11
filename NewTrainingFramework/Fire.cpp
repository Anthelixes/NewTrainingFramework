#include "stdafx.h"
#include "Fire.h"
#include "Globals.h"
#include "sceneManager.h"

Fire::Fire()
{
}

Fire::Fire(float dispMax):dispMax(dispMax){}

void Fire::Draw() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(shader->getId());

	Camera *x;
	x = SceneManager::getInstance()->getActiveCamera();

	glBindBuffer(GL_ARRAY_BUFFER, model->getVboId());
	if (!SceneManager::getInstance()->debug)
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getIboId());
	else
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->getWIboId());

	if (shader->dispMaxUniform != -1) {
		glUniform1f(shader->dispMaxUniform, dispMax);
	}
	if (shader->uTimeUniform != -1) {
		glUniform1f(shader->uTimeUniform, uTime);
	}

	SceneObject::SendCommonData();

	if (!SceneManager::getInstance()->debug)
		glDrawElements(GL_TRIANGLES, model->getNrInd(), GL_UNSIGNED_SHORT, (void *)0);

	else
		glDrawElements(GL_LINES, model->getNrInd() * 2, GL_UNSIGNED_SHORT, (void *)0);//

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Fire::Update() {
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

Fire::~Fire()
{
}
