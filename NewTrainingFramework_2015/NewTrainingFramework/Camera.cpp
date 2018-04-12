#pragma once
#include "stdafx.h"
#include "Camera.h"
#include "../Utilities/Math.h"

Camera::Camera()
{
	this->position = Vector3(0.0,0.0,1.0);
	this->target = Vector3(0.0,0.0,0.0);
	this->up = Vector3(0.0, 1.0, 0.0);
	this->moveSpeed = 0.8;
	this->rotateSpeed = 0.5;
	this->Near = 0.2;
	this->Far = 5000.0;
	this->fov = 45.0;

	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();
	xAxis = zAxis.Cross(yAxis).Normalize();

	Matrix T, R, Tinv, Rinv;

	R.m[0][0] = xAxis.x;
	R.m[0][1] = xAxis.y;
	R.m[0][2] = xAxis.z;
	R.m[0][3] = 0;
	R.m[1][0] = yAxis.x;
	R.m[1][1] = yAxis.y;
	R.m[1][2] = yAxis.z;
	R.m[1][3] = 0;
	R.m[2][0] = zAxis.x;
	R.m[2][1] = zAxis.y;
	R.m[2][2] = zAxis.z;
	R.m[2][3] = 0;
	R.m[3][0] = 0;
	R.m[3][1] = 0;
	R.m[3][2] = 0;
	R.m[3][3] = 1;
	T.SetTranslation(position.x, position.y, position.z);
	worldMatrix = R * T;
	Tinv = T.SetTranslation(-position.x, -position.y, -position.z);
	Rinv = R.Transpose();
	viewMatrix = Tinv * Rinv;
}
Camera::Camera(Vector3 position, Vector3 target, Vector3 up, GLfloat moveSpeed, GLfloat rotateSpeed, GLfloat Near, GLfloat Far, GLfloat fov, GLfloat deltatime)
{
	this->position = position;
	this->target = target;
	this->up = up;
	this->moveSpeed = moveSpeed;
	this->rotateSpeed = rotateSpeed;
	this->Near = Near;
	this->Far = Far;
	this->fov = fov;

	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();
	xAxis = zAxis.Cross(yAxis).Normalize();

	Matrix T, R, Tinv, Rinv;

	R.m[0][0] = xAxis.x;
	R.m[0][1] = xAxis.y;
	R.m[0][2] = xAxis.z;
	R.m[0][3] = 0;
	R.m[1][0] = yAxis.x;
	R.m[1][1] = yAxis.y;
	R.m[1][2] = yAxis.z;
	R.m[1][3] = 0;
	R.m[2][0] = zAxis.x;
	R.m[2][1] = zAxis.y;
	R.m[2][2] = zAxis.z;
	R.m[2][3] = 0;
	R.m[3][0] = 0;
	R.m[3][1] = 0;
	R.m[3][2] = 0;
	R.m[3][3] = 1;
	T.SetTranslation(position.x, position.y, position.z);
	worldMatrix = R * T;
	Tinv = T.SetTranslation(-position.x, -position.y, -position.z);
	Rinv = R.Transpose();
	viewMatrix = Tinv * Rinv;
}

void Camera::moveOz(GLfloat directie)
{
	forward = -(target - position).Normalize() * directie;
	vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::moveOy(GLfloat directie) {
	forward = -(target - position).Normalize() * directie;
	vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::moveOx(GLfloat directie) {
	forward = -(target - position).Normalize() * directie;
	vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::rotateOy(GLfloat directie)
{
	Vector4 localTarget;
	Vector4 rotatedTarget;
	Matrix mRotateOY;

	mRotateOY.SetRotationY(rotateSpeed * deltaTime * directie);
	localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	(Vector4)rotatedTarget = (Vector4)localTarget * mRotateOY;
	(Vector4)target = rotatedTarget * worldMatrix;
	updateWorldView();
}

void Camera::rotateOx(GLfloat directie)
{
	Vector3 rotatedLocalUp;
	Vector3 localUp;
	Vector3 localTarget;
	Vector3 rotatedTarget;
	Matrix mRotateOX;

	mRotateOX.SetRotationX(rotateSpeed * deltaTime * directie);
	(Vector4)rotatedLocalUp = (Vector4)localUp * mRotateOX;
	(Vector4)up = (Vector4)rotatedLocalUp * worldMatrix;
	up = up.Normalize();
	(Vector4)localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	(Vector4)rotatedTarget = (Vector4)localTarget * mRotateOX;
	(Vector4) target = (Vector4)rotatedTarget * worldMatrix;
	updateWorldView();
}

void Camera::rotateOz(GLfloat directie)
{
	Vector3 rotatedLocalUp;
	Vector4 localUp(0, 1, 0);
	Vector3 localTarget;
	Vector3 rotatedTarget;
	Matrix mRotateOZ;

	mRotateOZ.SetRotationZ(rotateSpeed * deltaTime * directie);
	(Vector4)rotatedLocalUp = (Vector4)localUp * mRotateOZ;
	(Vector4)up = (Vector4)rotatedLocalUp * worldMatrix;
	up = up.Normalize();
	(Vector4)localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	(Vector4)rotatedTarget = (Vector4)localTarget * mRotateOZ;
	(Vector4)target = (Vector4)rotatedTarget * worldMatrix;
	updateWorldView();
}

void Camera::updateWorldView() {
	Matrix T;
	Matrix R;
	Matrix Tinv;
	Matrix Rinv;

	R.m[0][0] = xAxis.x;
	R.m[0][1] = xAxis.y;
	R.m[0][2] = xAxis.z;
	R.m[0][3] = 0;
	R.m[1][0] = yAxis.x;
	R.m[1][1] = yAxis.y;
	R.m[1][2] = yAxis.z;
	R.m[1][3] = 0;
	R.m[2][0] = zAxis.x;
	R.m[2][1] = zAxis.y;
	R.m[2][2] = zAxis.z;
	R.m[2][3] = 0;
	R.m[3][0] = 0;
	R.m[3][1] = 0;
	R.m[3][2] = 0;
	R.m[3][3] = 1;
	T.SetTranslation(position.x, position.y, position.z);
	worldMatrix = R * T;
	Tinv = T.SetTranslation(-position.x, -position.y, -position.z);
	Rinv = R.Transpose();
	viewMatrix = Tinv * Rinv;
}
Camera::~Camera()
{
}

Matrix Camera::getView() {
	return viewMatrix;
}

float Camera::getFOV() {
	return fov;
}
float Camera::getNear() {
	return Near;
}
float Camera::getFar() {
	return Far;
}



void Camera::set_DeltaTime(float aux) {
	deltaTime = aux;
}