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
#include "SkyBox.h"
#include "Fire.h"
#include "Ligth.h"

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

//Reads from xml property with rgb tags
void static readVector3ColorFromXml(Vector3 &property, xml_node<>* node) {
	property.x = std::stof(node->first_node("r")->value());
	property.y = std::stof(node->first_node("g")->value());
	property.z = std::stof(node->first_node("b")->value());
}

//Reads from xml property with xyz tags
void static readVector3XYZFromXml(Vector3& property, xml_node<>* node) {
	property.x = std::stof(node->first_node("x")->value());
	property.y = std::stof(node->first_node("y")->value());
	property.z = std::stof(node->first_node("z")->value());
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
	xml_node<>* fog = root->first_node("fog");
	xml_node<>* ligths = root->first_node("ligths");

	if (fog) {
		SceneManager::spInstance->smallR = std::stof(fog->first_node("r")->value());
		SceneManager::spInstance->bigR = std::stof(fog->first_node("R")->value());
		xml_node<>* color = fog->first_node("color");
		if (color) {
			readVector3ColorFromXml(SceneManager::spInstance->fogColor, color);
		}
	}
	
	if (ligths) {

		if (ligths->first_node("ambientalLigth")) {
			readVector3ColorFromXml(SceneManager::GetInstance()->ambientalLigth, ligths->first_node("ambientalLigth"));
		}

		for (xml_node<>* ligth = ligths->first_node("ligth"); ligth; ligth = ligth->next_sibling("ligth")) {
			Ligth* newLigth = new Ligth();
			int id = std::stoi(ligth->first_attribute()->value());
			std::cout << "Ligth id: " << id << '\n';
			if (ligth->first_node("position")) {
				readVector3XYZFromXml(newLigth->position, ligth->first_node("position"));
			}
			if (ligth->first_node("specColor")) {
				readVector3ColorFromXml(newLigth->specColor, ligth->first_node("specColor"));
			}
			if (ligth->first_node("diffColor")) {
				readVector3ColorFromXml(newLigth->diffColor, ligth->first_node("diffColor"));
			}
			if (ligth->first_node("specPower")) {
				newLigth->specPower = std::stof(ligth->first_node("specPower")->value());
			}
			SceneManager::GetInstance()->currentSceneLights.insert({ id,newLigth });
		}
	}

	xml_node<>* objects = root->first_node("objects");

	for (xml_node<>* object = objects->first_node("object"); object; object = object->next_sibling("object")) {

		SceneObject* newObject = new SceneObject();
		std::string type = object->first_node("type")->value();
		std::cout << type << std::endl;
		if (type == "terrain") {
			newObject = new Terrain();
			if (object->first_node("inaltimi")) {
				readVector3ColorFromXml(newObject->color, object->first_node("inaltimi"));
			}
		}
		else if (type == "skyBox") {
			newObject = new SkyBox();
		}
		else if (type == "fire") {
			newObject = new Fire();
			Fire* fireObj = static_cast<Fire*>(newObject);
			if (fireObj) {
				fireObj->u_DispMax = std::stof(object->first_node("u_DispMax")->value());
			}
		}
		newObject->id = std::stoi(object->first_attribute("id")->value());

		if (object->first_node("position")) {
			readVector3XYZFromXml(newObject->position, object->first_node("position"));
		}

		if (object->first_node("rotation")) {
			readVector3XYZFromXml(newObject->rotation, object->first_node("rotation"));
		}

		if (object->first_node("scale")) {
			readVector3XYZFromXml(newObject->scale, object->first_node("scale"));
		}

		if (object->first_node("color")) {
			readVector3ColorFromXml(newObject->color, object->first_node("color"));
		}

		if (object->first_node("followingCamera")) {
			if (object->first_node("followingCamera")->first_node("ox"))
				newObject->followingCamera.x = 1;
			if (object->first_node("followingCamera")->first_node("oy"))
				newObject->followingCamera.y = 1;
			if (object->first_node("followingCamera")->first_node("oz"))
				newObject->followingCamera.z = 1;
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
			std::cout << type << std::endl;
			newObject->model = new Model();
			newObject->model->generateModel();
		}

		xml_node<>* textureRoot = object->first_node("textures");
		int textureId = -1;
		if (textureRoot){
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

		if (modelId != -1){
			newObject->model = resourceManager->loadModel(modelId);
		}

		if (shaderId != -1){
			newObject->shader = resourceManager->loadShader(shaderId);
		}

		SceneManager::spInstance->currentSceneObjects.push_back(newObject);
	}
}

void SceneManager::Draw(ESContext* esContext) {	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_CULL_FACE);

	for (SceneObject* object : currentSceneObjects) {
		object->Draw(esContext);
		object->Update();
	}

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}    