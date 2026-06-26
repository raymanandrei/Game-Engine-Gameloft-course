#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"

Camera::Camera()
{
	this->position = Vector3(0.0, 0.0, 1.0);
	this->target = Vector3(0.0, 0.0, 0.0);
	this->up = Vector3(0.0, 1.0, 0.0);
	this->moveSpeed = 200.0;
	this->rotateSpeed = 2;
	this->nearPlane = 1;
	this->farPlane = 30000.0;
	this->fov =  0.78;

	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();
	xAxis = zAxis.Cross(yAxis).Normalize();
	updateWorldView();
	perspectiveMatrix.SetPerspective(fov, (float)Globals::screenWidth / Globals::screenHeight, nearPlane, farPlane);
}

Camera::~Camera()
{
}

void Camera::moveOx(GLfloat sens) {

	Vector3 forward = xAxis * sens;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;

	updateWorldView();
}

void Camera::moveOy(GLfloat sens) {

	Vector3 forward = yAxis * sens;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;

	updateWorldView();
}

void Camera::moveOz(GLfloat sens) {

	Vector3 forward = -(target - position).Normalize() * sens;
	Vector3 vectorDeplasare = forward * moveSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;

	updateWorldView();

}

void Camera::rotateOx(GLfloat sens)
{
	float unghiRotatie = sens * rotateSpeed * deltaTime;

	Matrix mRotateOX;
	mRotateOX.SetRotationX(unghiRotatie);

	Vector4 localUp = Vector4(0, 1, 0, 0);
	Vector4 rotatedLocalUp = localUp * mRotateOX;

	up = (rotatedLocalUp * worldMatrix).toVector3();
	up = up.Normalize();

	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOX;

	target = (rotatedTarget * worldMatrix).toVector3();

	updateWorldView();
}

void Camera::rotateOy(GLfloat sens)
{
	float unghiRotatie = sens * rotateSpeed * deltaTime;

	Matrix mRotateOY;
	mRotateOY.SetRotationY(unghiRotatie);

	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOY;

	target = (rotatedTarget * worldMatrix).toVector3();

	updateWorldView();
}

void Camera::rotateOz(GLfloat sens) {

	float unghiRotatie = sens * rotateSpeed * deltaTime;

	Matrix mRotateOZ;
	mRotateOZ.SetRotationZ(unghiRotatie);

	Vector4 localUp = Vector4(0, 1, 0, 0);
	Vector4 rotatedLocalUp = localUp * mRotateOZ;

	up = (rotatedLocalUp * worldMatrix).toVector3();
	up = up.Normalize();

	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOZ;

	target = (rotatedTarget * worldMatrix).toVector3();

	updateWorldView();
}

void Camera::updateAxes() {
	zAxis = -(target - position).Normalize(); 
	yAxis = up.Normalize();
	xAxis = zAxis.Cross(yAxis).Normalize();
}

void Camera::updateWorldView() {
	updateAxes();
	Matrix R;
	R.SetIdentity();
	R.m[0][0] = xAxis.x;
	R.m[0][1] = xAxis.y;
	R.m[0][2] = xAxis.z;

	R.m[1][0] = yAxis.x;
	R.m[1][1] = yAxis.y;
	R.m[1][2] = yAxis.z;

	R.m[2][0] = zAxis.x;
	R.m[2][1] = zAxis.y;
	R.m[2][2] = zAxis.z;

	Matrix T;

	T.SetIdentity();
	T.SetTranslation(position);

	worldMatrix = R * T;

	Matrix T1;

	T1.SetIdentity();
	T1.SetTranslation(-position);
	
	Matrix R1;

	R1 = R.Transpose();

	viewMatrix = T1 * R1;
}

void Camera::setDeltaTime(GLfloat dt)
{
	deltaTime = dt;
}

