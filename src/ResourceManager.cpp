#include "ResourceManager.hpp"
#include "../Utilities/pugixml-1.16/pugixml.hpp"
#include "ModelResource.hpp"
#include "Vertex.hpp"
#include "stdafx.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

ResourceManager *ResourceManager::spInstance = nullptr;

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
  delete spInstance;
  spInstance = nullptr;
}

void ResourceManager::Init() {

  std::cout << "ResourceManager::Init()" << '\n';

  char *xmlPath = "resourceManager.xml";

  ResourceManager::spInstance->textureTypes["GL_LINEAR"] = GL_LINEAR;
  ResourceManager::spInstance->textureTypes["GL_REPEAT"] = GL_REPEAT;
  ResourceManager::spInstance->textureTypes["GL_CLAMP_TO_EDGE"] = GL_CLAMP_TO_EDGE;
  ResourceManager::spInstance->textureTypes["CLAMP_TO_EDGE"] = GL_CLAMP_TO_EDGE;
  ResourceManager::spInstance->textureTypes["2d"] = GL_TEXTURE_2D;
  ResourceManager::spInstance->textureTypes["cube"] = GL_TEXTURE_CUBE_MAP;

  pugi::xml_document doc;
  pugi::xml_parse_result xmlFile = doc.load_file(xmlPath);

  if (!xmlFile) {
    std::cout << "Failed to load " << xmlPath << '\n';
  }

  pugi::xml_node root = doc.child("resourceManager");
  pugi::xml_node models = root.child("models");
  pugi::xml_node shaders = root.child("shaders");
  pugi::xml_node textures = root.child("textures");

  pugi::xml_node folder = models.child("folder");
  const char *folderPath = folder.first_attribute().value();

  for (pugi::xml_node model = folder.child("model"); model; model = model.next_sibling("model")) {
    const int id = std::stoi(model.first_attribute().value());
    std::string file = model.child_value("file");

    ResourceManager::spInstance->modelResources[id] = new ModelResource();
    ResourceManager::spInstance->modelResources[id]->id = std::to_string(id);
    ResourceManager::spInstance->modelResources[id]->file = folderPath + file;
  }

  folder = shaders.child("folder");
  const char *path = folder.first_attribute().value();

  for (pugi::xml_node shader = folder.child("shader"); shader; shader = shader.next_sibling("shader")) {
    int id = std::stoi(shader.first_attribute().value());

    std::string vs = shader.child_value("vs");
    std::string fs = shader.child_value("fs");

    ResourceManager::spInstance->shaderResources[id] = new ShaderResource();
    ResourceManager::spInstance->shaderResources[id]->id = std::to_string(id);
    ResourceManager::spInstance->shaderResources[id]->vs = path + vs;
    ResourceManager::spInstance->shaderResources[id]->fs = path + fs;

    std::cout << ResourceManager::spInstance->shaderResources[id]->vs << " "
              << ResourceManager::spInstance->shaderResources[id]->fs << '\n';
  }

  folder = textures.child("folder");
  path = folder.first_attribute().value();

  for (pugi::xml_node tex = folder.child("texture"); tex; tex = tex.next_sibling("texture")) {
    int id = std::stoi(tex.first_attribute().value());
    std::string type = tex.attribute("type").value();
    std::string file = tex.child_value("file");

    std::string minFilter = tex.child_value("min_filter");
    std::string magFilter = tex.child_value("mag_filter");
    std::string wrapS = tex.child_value("wrap_s");
    std::string wrapT = tex.child_value("wrap_t");

    ResourceManager::spInstance->textureResources[id] = new TextureResource();
    ResourceManager::spInstance->textureResources[id]->id = id;
    ResourceManager::spInstance->textureResources[id]->type = ResourceManager::spInstance->textureTypes[type];
    ResourceManager::spInstance->textureResources[id]->file = path + file;
    ResourceManager::spInstance->textureResources[id]->min_filter =
        ResourceManager::spInstance->textureTypes[minFilter];
    ResourceManager::spInstance->textureResources[id]->mag_filter =
        ResourceManager::spInstance->textureTypes[magFilter];
    ResourceManager::spInstance->textureResources[id]->wrap_s = ResourceManager::spInstance->textureTypes[wrapS];
    ResourceManager::spInstance->textureResources[id]->wrap_t = ResourceManager::spInstance->textureTypes[wrapT];

    std::cout << std::string(tex.child_value("wrap_s")) << '\n';
  }
  std::cout << "ResourceManager::Init() end" << '\n';
}

Model *ResourceManager::loadModel(int id) {

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

Shader *ResourceManager::loadShader(int id) {
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

Texture *ResourceManager::loadTexture(int id) {
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

ResourceManager *ResourceManager::GetInstance() {
  if (!spInstance)
    spInstance = new ResourceManager();
  return spInstance;
}
