#include "headers/Camera.hpp"
#include "../Utilities/pugixml-1.16/pugixml.hpp"
#include "headers/SceneManager.hpp"
#include "headers/XML.hpp"
#include "headers/stdafx.hpp"
#include <fstream>
#include <iostream>

Camera::Camera() {

  char *xmlPath = "sceneManager.xml";

  pugi::xml_document doc;
  pugi::xml_parse_result xmlFile = doc.load_file(xmlPath);

  if (!xmlFile) {
    std::cout << "sceneManger XML not found\n";
    return;
  }

  pugi::xml_node cameraNode = doc.child("sceneManager").child("cameras").child("camera");
  pugi::xml_node cameraSize = doc.child("sceneManager").child("defaultScreenSize");

  printf("Create camera instance");
  readVector3XYZFromXml(position, cameraNode.child("position"));
  readVector3XYZFromXml(target, cameraNode.child("target"));
  readVector3XYZFromXml(up, cameraNode.child("up"));
  moveSpeed = std::stof(cameraNode.child_value("moveSpeed"));
  rotateSpeed = std::stof(cameraNode.child_value("rotationSpeed"));
  nearPlane = std::stof(cameraNode.child_value("nearPlane"));
  farPlane = std::stof(cameraNode.child_value("farPlane"));
  fov = std::stof(cameraNode.child_value("fov"));

  std::cout << "Camera position: " << nearPlane << ", " << fov << ", " << position.z << std::endl;

  zAxis = -(target - position).Normalize();
  yAxis = up.Normalize();
  xAxis = zAxis.Cross(yAxis).Normalize();
  updateWorldView();

  float w = std::stof(cameraSize.child_value("width"));
  float h = std::stof(cameraSize.child_value("height"));
  float aspectRatio = w / h;

  perspectiveMatrix.SetPerspective(fov, aspectRatio, nearPlane, farPlane);
}

Camera::~Camera() {
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

void Camera::rotateOx(GLfloat sens) {
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

void Camera::rotateOy(GLfloat sens) {
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

void Camera::setDeltaTime(GLfloat dt) {
  deltaTime = dt;
}
