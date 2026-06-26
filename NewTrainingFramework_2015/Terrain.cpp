#include "stdafx.h"
#include <iostream>
#include "Terrain.h"
#include "Vertex.h"
#include "SceneManager.h"

Terrain::Terrain() {
	this->cellSize = 500;
	this->nrCells = 8;
	this->blendTextureOffset = Vector2(0.0f, 0.0f);
}

void Terrain::sendSpecificData() {

	if (this->shader->sr->blendTextureOffset != -1) {
		glUniform2f(
			this->shader->sr->blendTextureOffset,
			blendTextureOffset.x,
			blendTextureOffset.y
		);
	}

	if (this->shader->sr->uv2Attribute != -1) {
		glEnableVertexAttribArray(this->shader->sr->uv2Attribute);
		glVertexAttribPointer(this->shader->sr->uv2Attribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, uv2));
	}

	if (this->shader->sr->u_height != -1) {
		glUniform3f(this->shader->sr->u_height, this->color.x, this->color.y, this->color.z);
	}
}

void Terrain::Update() {
	SceneManager* sceneManager = SceneManager::GetInstance();
	GLfloat dx = sceneManager->camera.position.x - this->position.x;
	GLfloat dz = sceneManager->camera.position.z - this->position.z;
	float textureStep = 1.0 / this->nrCells;

	//std::cout << this->model->mr->id << " " << dx << " " << dz << std::endl;
	//std::cout << textureStep << std::endl;
	if (dx > this->cellSize)
	{
		this->position.x += this->cellSize;
		this->blendTextureOffset.x += textureStep;
		std::cout << this->blendTextureOffset.x << std::endl;
	}
	else if (dx < -this->cellSize)
	{
		this->position.x -= this->cellSize;
		this->blendTextureOffset.x -= textureStep;
	}
	if (dz > this->cellSize)
	{
		this->position.z += this->cellSize;
		this->blendTextureOffset.y += textureStep;
	}
	else if (dz < -this->cellSize)
	{
		this->position.z -= this->cellSize;
		this->blendTextureOffset.y -= textureStep;
	}

	//std::cout << dx << " " << dz << std::endl;
}	