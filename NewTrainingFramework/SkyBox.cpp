#include "stdafx.h"
#include "SkyBox.h"
#include "SceneManager.h"
#include "Globals.h"

SkyBox::SkyBox()
{
}

SkyBox::SkyBox(float offsetY) {
	this->offsetY = offsetY;
}

void SkyBox::Draw() {
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

void SkyBox::Update() {
	Camera *x;
	x = SceneManager::getInstance()->getActiveCamera();

	Matrix scal, rx, ry, rz, trans, world;

	scal.SetScale(scale);
	rx.SetRotationX(rotation.x);
	ry.SetRotationY(rotation.y);
	rz.SetRotationZ(rotation.z);

	trans.SetTranslation(Vector3(x->getPos().x, offsetY, x->getPos().z));

	world = scal * rx * ry * rz * trans;
	mvp = world * x->viewMatrix * x->Perspect;
}

SkyBox::~SkyBox()
{
}
