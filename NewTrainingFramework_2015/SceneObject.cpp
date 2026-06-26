#include "stdafx.h"
#include <iostream>
#include "SceneObject.h";
#include "SceneManager.h"
#include "Camera.h"
#include "Ligth.h"
#include "Vertex.h"

SceneObject::SceneObject() {
}

SceneObject::~SceneObject() {
}

void SceneObject::sendCommonData() {

	//std::cout << SceneManager::GetInstance()->camera.position.x << " " << SceneManager::GetInstance()->camera.position.y << " " << SceneManager::GetInstance()->camera.position.z << std::endl;
	//std::cout << "Sending common data for object ID: " << this->id << std::endl;
	glBindBuffer(GL_ARRAY_BUFFER,this->model->vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->model->iboId);
	//std::cout << "Bound VBO ID: " << this->model->vboId << " and IBO ID: " << this->model->iboId << std::endl;

	if (this->shader->sr->positionAttribute != -1){
		glEnableVertexAttribArray(this->shader->sr->positionAttribute);
		glVertexAttribPointer(this->shader->sr->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (this->shader->sr->uvAttribute != -1){
		glEnableVertexAttribArray(this->shader->sr->uvAttribute);
		glVertexAttribPointer(this->shader->sr->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, uv));
	}

	if (this->shader->sr->a_norm != -1) {
		glEnableVertexAttribArray(this->shader->sr->a_norm);
		glVertexAttribPointer(this->shader->sr->a_norm,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const GLvoid *)offsetof(Vertex,norm ));
	}

	Matrix rotation = Matrix().SetRotationX(this->rotation.x) * Matrix().SetRotationX(this->rotation.y) * Matrix().SetRotationZ(this->rotation.z);

	Matrix model = Matrix().SetScale(this->scale.x, this->scale.y, this->scale.z) * rotation * Matrix().SetTranslation(this->position.x, this->position.y, this->position.z);

	Matrix MVP = model * SceneManager::GetInstance()->camera.viewMatrix * SceneManager::GetInstance()->camera.perspectiveMatrix;

	SceneManager* sceneManager = SceneManager::GetInstance();

	if (this->shader->sr->smallR != -1) {
		glUniform1f(this->shader->sr->smallR, sceneManager->smallR);
	}

	if (this->shader->sr->bigR != -1) {
		glUniform1f(this->shader->sr->bigR, sceneManager->bigR);
	}

	if (this->shader->sr->fogColor != -1) {
		glUniform3f(this->shader->sr->fogColor, sceneManager->fogColor.x, sceneManager->fogColor.y, sceneManager->fogColor.z);
	}

	if (this->shader->sr->matrixModel != -1) {
		glUniformMatrix4fv(this->shader->sr->matrixModel, 1, GL_FALSE, (float*)model.m);
	}

	if (this->shader->sr->cameraPosition != -1) {
		SceneManager* sceneManager = SceneManager::GetInstance();
		glUniform3f(this->shader->sr->cameraPosition, sceneManager->camera.position.x, sceneManager->camera.position.y, sceneManager->camera.position.z);
	}

	if (this->shader->sr->matrixCamera != -1) {
		glUniformMatrix4fv(this->shader->sr->matrixCamera, 1, GL_FALSE, (float*)MVP.m);
	}

	if (this->shader->sr->colorAttribute != -1) {
		glEnableVertexAttribArray(this->shader->sr->colorAttribute);
		glVertexAttribPointer(this->shader->sr->colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)offsetof(Vertex, color));
	}

	if (this->shader->sr->objectColor != -1) {
		glUniform3f(this->shader->sr->objectColor, this->color.x, this->color.y, this->color.z);
	}

	if (this->texture.size()) {

		for (int i = 0; i < this->texture.size();i++) {
			//std::cout << "Texture with id:" << this->texture[i]->tr->id << "and file:" << this->texture[i]->tr->file << '\n';
			glUniform1i(this->shader->sr->textureUniform[i], i);
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(this->texture[i]->tr->type, this->texture[i]->tr->id);
		}		
	}
	
	Ligth *ligth = SceneManager::GetInstance()->currentSceneLights[1];

	if (this->shader->sr->lightPosition != -1) {
		glUniform3f(this->shader->sr->lightPosition, ligth->position.x, ligth->position.y, ligth->position.z);
	}

	if (this->shader->sr->c_lightDiff != -1) {
		glUniform3f(this->shader->sr->c_lightDiff, ligth->diffColor.x, ligth->diffColor.y, ligth->diffColor.z);
	}

	if (this->shader->sr->c_lightSpec != -1) {
		glUniform3f(this->shader->sr->c_lightSpec, ligth->specColor.x, ligth->specColor.y, ligth->specColor.z);
	}

	if (this->shader->sr->SpecPower != -1) {
		glUniform1f(this->shader->sr->SpecPower, ligth->specPower);
	}

	if (this->shader->sr->c_amb != -1) {
		glUniform3f(this->shader->sr->c_amb, SceneManager::GetInstance()->ambientalLigth.x, SceneManager::GetInstance()->ambientalLigth.y, SceneManager::GetInstance()->ambientalLigth.z);
	}
}

void SceneObject::sendSpecificData() {
	return;
}

void SceneObject::Draw(ESContext* esContext) {
	
	glUseProgram(this->shader->programId);

	sendCommonData();

	sendSpecificData();

	glDrawElements(GL_TRIANGLES, this->model->nrIndici, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SceneObject::Update() {
	SceneManager* sceneManager = SceneManager::GetInstance();
}