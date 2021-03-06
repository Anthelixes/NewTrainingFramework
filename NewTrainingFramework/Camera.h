#pragma once
#include "../Utilities/Math.h"

class Camera
{
	Vector3 position;
	Vector3 target;
	Vector3 up;
	GLfloat moveSpeed;
	GLfloat rotateSpeed;
	GLfloat Near;
	GLfloat Far;
	GLfloat fov;
	GLfloat deltaTime;
	Vector3 xAxis;
	Vector3 yAxis;
	Vector3 zAxis;
	Vector3 forward;
	Vector3 vectorDeplasare;

public:

	Matrix Perspect;
	Matrix viewMatrix;
	Matrix worldMatrix;

	Camera();
	~Camera();
	Camera(Vector3, Vector3, Vector3, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	void moveOx(GLfloat);
	void moveOy(GLfloat);
	void moveOz(GLfloat);
	void rotateOx(GLfloat);
	void rotateOy(GLfloat);
	void rotateOz(GLfloat);
	void updateWorldView();
	void setDeltaTime(float);
	Matrix getView();
	float getFOV();
	float getNear();
	float getFar();
	Vector3&	getPos();
};