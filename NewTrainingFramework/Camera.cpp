#include "stdafx.h"
#include "../Utilities/rapidxml/rapidxml.hpp"
#include "Camera.h"
#include "SceneManager.h"
#include "XML.h"
#include <fstream>
#include <iostream>

Camera::Camera()
{
	std::string xmlPath = "..\\sceneManager.xml";

	rapidxml::xml_document<> doc;
	std::ifstream xmlFile(xmlPath);
	std::vector<char> buffer{ std::istreambuf_iterator<char>(xmlFile), std::istreambuf_iterator<char>() };

	buffer.push_back('\0');

	doc.parse<0>(&buffer[0]);

	rapidxml::xml_node<>* cameraNode = doc.first_node("sceneManager")->first_node("cameras")->first_node("camera");
	rapidxml::xml_node<>* cameraSize = doc.first_node("sceneManager")->first_node("defaultScreenSize");

	readVector3XYZFromXml(position,cameraNode->first_node("position"));
	readVector3XYZFromXml(target, cameraNode->first_node("target"));
	readVector3XYZFromXml(up, cameraNode->first_node("up"));
	moveSpeed = std::stof(cameraNode->first_node("moveSpeed")->value());
	rotateSpeed = std::stof(cameraNode->first_node("rotationSpeed")->value());
	nearPlane = std::stof(cameraNode->first_node("nearPlane")->value());;
	farPlane = std::stof(cameraNode->first_node("farPlane")->value());;
	fov = std::stof(cameraNode->first_node("fov")->value());
	
	std::cout << "Camera position: " << nearPlane << ", " << fov << ", " << position.z << std::endl;

	zAxis = -(target - position).Normalize();
	yAxis = up.Normalize();
	xAxis = zAxis.Cross(yAxis).Normalize();
	updateWorldView();

	float w = std::stof(cameraSize->first_node("width")->value());
	float h = std::stof(cameraSize->first_node("height")->value());
	float aspectRatio = w / h;

	perspectiveMatrix.SetPerspective(fov, aspectRatio, nearPlane, farPlane);
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

