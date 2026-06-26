#include "stdafx.h"
#include "../Utilities/rapidxml/rapidxml.hpp"
#include "ResourceManager.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Vertex.h"
#include "ModelResource.h"

using namespace rapidxml;

ResourceManager* ResourceManager::spInstance = nullptr;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	spInstance = nullptr;
}

void ResourceManager::Init() {

	std::string xmlPath = "..\\resourceManager.xml";

	ResourceManager::spInstance->textureTypes["GL_LINEAR"] = GL_LINEAR;
	ResourceManager::spInstance->textureTypes["GL_REPEAT"] = GL_REPEAT;
	ResourceManager::spInstance->textureTypes["GL_CLAMP_TO_EDGE"] = GL_CLAMP_TO_EDGE;
	ResourceManager::spInstance->textureTypes["CLAMP_TO_EDGE"] = GL_CLAMP_TO_EDGE;
	ResourceManager::spInstance->textureTypes["2d"] = GL_TEXTURE_2D;	
	ResourceManager::spInstance->textureTypes["cube"] = GL_TEXTURE_CUBE_MAP;


	rapidxml::xml_document<> doc;
	std::ifstream xmlFile(xmlPath);
	std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile)), std::istreambuf_iterator<char>());

	buffer.push_back('\0');

	doc.parse<0>(&buffer[0]);

	xml_node<>* root = doc.first_node("resourceManager");
	xml_node<>* models = root->first_node("models");
	xml_node<>* shaders = root->first_node("shaders");
	xml_node<>* textures = root->first_node("textures");
	xml_node<>* folder = models->first_node("folder");

	for (xml_node<>* folder = models->first_node("folder");folder; folder = folder->next_sibling("folder")){
		const char* folderPath = folder->first_attribute("path")->value();

		for (xml_node<>* model = folder->first_node("model");model; model = model->next_sibling("model")){
			const int id = std::stoi(model->first_attribute("id")->value());
			xml_node<>* file = model->first_node("file");

			ResourceManager::spInstance->modelResources[id] = new ModelResource();
			ResourceManager::spInstance->modelResources[id]->id = std::to_string(id);	
			ResourceManager::spInstance->modelResources[id]->file = folderPath + std::string(file->value());

			//std::cout << "Loaded model ID: " << id << " File: ";
			//std::cout << ResourceManager::spInstance->modelResources[id]->file << std::endl;
		}
	}

	folder = shaders->first_node("folder");
	const char* path = folder->first_attribute("path")->value();

	for (xml_node<>* shader = folder->first_node("shader");shader; shader = shader->next_sibling("shader")){
		int id = std::stoi(shader->first_attribute("id")->value());

		const char* vs = shader->first_node("vs")->value();
		const char* fs = shader->first_node("fs")->value();
		
		//std::cout << "Loaded shader ID: " << id << " VS: " << path + std::string(vs) << " FS: " << path + std::string(fs) << std::endl;

		ResourceManager::spInstance->shaderResources[id] = new ShaderResource();
		ResourceManager::spInstance->shaderResources[id]->id = std::to_string(id);
		ResourceManager::spInstance->shaderResources[id]->vs = path + std::string(vs);
		ResourceManager::spInstance->shaderResources[id]->fs = path + std::string(fs);
	}
	
	folder = textures->first_node("folder");
	path = folder->first_attribute("path")->value();

	for (xml_node<>* tex = folder->first_node("texture");tex; tex = tex->next_sibling("texture"))
	{
		int id = std::stoi(tex->first_attribute("id")->value());
		const char* type = tex->first_attribute("type")->value();

		ResourceManager::spInstance->textureResources[id] = new TextureResource();
		ResourceManager::spInstance->textureResources[id]->id = id;
		ResourceManager::spInstance->textureResources[id]->type = ResourceManager::spInstance->textureTypes[type];
		ResourceManager::spInstance->textureResources[id]->file = path + std::string(tex->first_node("file")->value());
		ResourceManager::spInstance->textureResources[id]->min_filter = ResourceManager::spInstance->textureTypes[tex->first_node("min_filter")->value()];
		ResourceManager::spInstance->textureResources[id]->mag_filter = ResourceManager::spInstance->textureTypes[tex->first_node("mag_filter")->value()];
		ResourceManager::spInstance->textureResources[id]->wrap_s = ResourceManager::spInstance->textureTypes[tex->first_node("wrap_s")->value()];
		ResourceManager::spInstance->textureResources[id]->wrap_t = ResourceManager::spInstance->textureTypes[tex->first_node("wrap_t")->value()];
	}
	xmlFile.close();
}

Model* ResourceManager::loadModel(int id){

	if (loadedModels[id])
		return loadedModels[id];
	else {
		loadedModels[id] = new Model();
		loadedModels[id]->mr = modelResources[id];	
		if (loadedModels[id]->Load())
			return loadedModels[id];
		return nullptr;
	}
}

Shader* ResourceManager::loadShader(int id){
	if (loadedShaders[id])
		return loadedShaders[id];
	else {
		loadedShaders[id] = new Shader();
		loadedShaders[id]->sr = shaderResources[id];
		if (loadedShaders[id]->Load())
			return loadedShaders[id];
		return nullptr;
	}
}	

Texture* ResourceManager::loadTexture(int id){
	if (loadedTextures[id])
		return loadedTextures[id];
	else {
		loadedTextures[id] = new Texture();
		loadedTextures[id]->tr = textureResources[id];
		if (loadedTextures[id]->Load())
			return loadedTextures[id];
		return nullptr;
	}
}

ResourceManager* ResourceManager::GetInstance() {
	if (!spInstance) 
		spInstance = new ResourceManager();
	return spInstance;
}
