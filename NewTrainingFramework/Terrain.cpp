#include "stdafx.h"
#include <iostream>
#include "Terrain.h"
#include "SceneManager.h"

void Terrain::Update() {
	SceneManager* sceneManager = SceneManager::GetInstance();
	int d = 500;
	int dx = sceneManager->camera.position.x - this->position.x;
	int dz = sceneManager->camera.position.z - this->position.z;

	std::cout << this->model->mr->id << " " << dx << " " << dz << std::endl;
	if (dx > d)
		this->position.x += d;
	else if (dx < -d)
		this->position.x -= d;
	if (dz > d)
		this->position.z += d;
	else if (dz < -d)
		this->position.z -= d;
	std::cout << dx << " " << dz << std::endl;
}	