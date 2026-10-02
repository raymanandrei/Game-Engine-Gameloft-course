#include "SkyBox.hpp"
#include "SceneManager.hpp"
#include "Vertex.hpp"
#include "stdafx.hpp"
#include <iostream>

void SkyBox::Update() {
  // std::cout << this->position.x << " " << this->position.y << " " <<
  // this->position.z << '\n';
  SceneManager *sceneManager = SceneManager::GetInstance();
  if (this->followingCamera.x || this->followingCamera.z) {
    this->position.x = sceneManager->camera.position.x;
    this->position.z = sceneManager->camera.position.z;
  }
}

void SkyBox::sendSpecificData() {
}
