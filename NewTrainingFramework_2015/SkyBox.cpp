#include "stdafx.h"
#include <iostream>
#include "SkyBox.h"
#include "SceneManager.h"
#include "Vertex.h"

void SkyBox::Update() {
	//std::cout << this->position.x << " " << this->position.y << " " << this->position.z << '\n';
	SceneManager* sceneManager = SceneManager::GetInstance();
	if (this->followingCamera.x ||  this->followingCamera.z) {
		this->position.x = sceneManager->camera.position.x;
		this->position.z = sceneManager->camera.position.z;
	}
}

void SkyBox::sendSpecificData() {
}
