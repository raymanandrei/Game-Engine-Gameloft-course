#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "../Utilities/rapidxml/rapidxml.hpp"
#include "SceneManager.h"
#include "Globals.h"
#include "Camera.h"
#include "SceneObject.h"
#include "ResourceManager.h"
#include "Terrain.h"

using namespace rapidxml;

SceneManager* SceneManager::spInstance = nullptr;    

SceneManager* SceneManager::GetInstance() {
	if (spInstance == nullptr) 
		spInstance = new SceneManager();
	return spInstance;
}

SceneManager::SceneManager() {
	camera = Camera();
	totalTime = 0;
}

SceneManager::~SceneManager() {
	delete spInstance;
}

void SceneManager::Update(float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= Globals::frameTime) {
		camera.setDeltaTime(totalTime);
		totalTime = 0;
	}
}

void SceneManager::InitWindow(ESContext* esContext) {
	std::string xmlPath = "..\\sceneManager.xml";

	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* rootNode;
	std::ifstream xmlFile(xmlPath);
	std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());

	buffer.push_back('\0');

	doc.parse<0>(&buffer[0]);

	xml_node<>* root = doc.first_node("sceneManager");
	xml_node<>* gameName = root->first_node("gameName");
	xml_node<>* defaultScreenSize = root->first_node("defaultScreenSize");

	esCreateWindow(esContext, gameName->value(), std::stoi(defaultScreenSize->first_node("width")->value()), std::stoi(defaultScreenSize->first_node("height")->value()), ES_WINDOW_RGB | ES_WINDOW_DEPTH);
}

void SceneManager::Init() {
    
	std::string xmlPath = "..\\sceneManager.xml";

	rapidxml::xml_document<> doc;
	rapidxml::xml_node<>* rootNode;
	std::ifstream xmlFile(xmlPath);
	std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());

	buffer.push_back('\0');

	doc.parse<0>(&buffer[0]);

	xml_node<>* root = doc.first_node("sceneManager");
	xml_node<>* backgroundColor = root->first_node("backgroundColor");
	xml_node<>* controls = root->first_node("controls");
	xml_node<>* objects = root->first_node("objects");

	for (xml_node<>* object = objects->first_node("object"); object; object = object->next_sibling("object")) {

		SceneObject* newObject = new SceneObject();
		newObject->id = std::stoi(object->first_attribute("id")->value());
		newObject->position.x = std::stof(object->first_node("position")->first_node("x")->value());
		newObject->position.y = std::stof(object->first_node("position")->first_node("y")->value());
		newObject->position.z = std::stof(object->first_node("position")->first_node("z")->value());

		newObject->rotation.x = std::stof(object->first_node("rotation")->first_node("x")->value());
		newObject->rotation.y = std::stof(object->first_node("rotation")->first_node("y")->value());
		newObject->rotation.z = std::stof(object->first_node("rotation")->first_node("z")->value());

		newObject->scale.x = std::stof(object->first_node("scale")->first_node("x")->value());
		newObject->scale.y = std::stof(object->first_node("scale")->first_node("y")->value());
		newObject->scale.z = std::stof(object->first_node("scale")->first_node("z")->value());

		if (object->first_node("color")) {
			std::cout << "Loading color for object ID: " << newObject->id << std::endl;
			newObject->color.x = std::stof(object->first_node("color")->first_node("r")->value());
			newObject->color.y = std::stof(object->first_node("color")->first_node("g")->value());
			newObject->color.z = std::stof(object->first_node("color")->first_node("b")->value());
		}

		if (object->first_node("inaltimi")) {
			newObject->color.x = std::stof(object->first_node("inaltimi")->first_node("r")->value());
			newObject->color.y = std::stof(object->first_node("inaltimi")->first_node("g")->value());
			newObject->color.z = std::stof(object->first_node("inaltimi")->first_node("b")->value());
		}

		ResourceManager* resourceManager = ResourceManager::GetInstance();

		int modelId = -1;
		std::string modelStringId = object->first_node("model")->value();
		if (modelStringId != "generated")
		{
			std::cout << object->first_node("model")->value() << std::endl;
			modelId = std::stoi(object->first_node("model")->value());
		}
		else {
			newObject->model = new Model();
			bool ok = newObject->model->generateModel();
		}

		xml_node<>* textureRoot = object->first_node("textures");
		int textureId = -1;
		if (textureRoot)
		{
			xml_node<>* textureNode = textureRoot->first_node("texture");
			xml_attribute<>* idAttr = textureNode->first_attribute("id");
			for (xml_node<>* textures = textureRoot->first_node("texture"); textures; textures = textures->next_sibling("texture"))
			{
				xml_attribute<>* idAttr = textures->first_attribute("id");
				textureId = std::stoi(idAttr->value());
				std::cout <<"TextureID :: " << textureId << '\n';
				std::cout << resourceManager->textureResources[textureId]->file << std::endl;
				Texture *text = resourceManager->loadTexture(textureId);
				if (text->tr)
					newObject->texture.push_back(text);
			}   
		}

		int shaderId = -1;
		shaderId = std::stoi(object->first_node("shader")->value());

		//std::cout << "Loading object ID: " << newObject->id << " Model ID: " << modelId << " Shader ID: " << shaderId << " Texture ID: " << std::endl;

		if (modelId != -1)
		{
			//std::cout << resourceManager->modelResources[modelId]->file << std::endl;
			newObject->model = resourceManager->loadModel(modelId);
		}

		if (shaderId != -1)
		{
			//std::cout << "Shader id:: " << shaderId << std::endl;
			//std::cout << resourceManager->shaderResources[shaderId]->fs << std::endl;
			newObject->shader = resourceManager->loadShader(shaderId);
			//std::cout << "Loaded shader program ID: " << newObject->shader->programId << std::endl;
			//std::cout << "Loaded shader vertex shader: " << newObject->shader->sr->vs << std::endl;
			//std::cout << "Loaded shader vertex shader: " << newObject->shader->sr->fs << std::endl;
		}

		SceneManager::spInstance->currentSceneObjects.push_back(newObject);
	}
}

void SceneManager::Draw(ESContext* esContext) {
	//printf("Drawing scene with %d objects.\n", currentSceneObjects.size());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_CULL_FACE);

	for (SceneObject* object : currentSceneObjects) {
		object->Draw(esContext);
		object->Update();
	}

}    