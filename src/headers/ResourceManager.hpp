#pragma once
#include "../Utilities/utilities.hpp"
#include <string>
#include <unordered_map>

#include "ModelResource.hpp"
#include "ShaderResource.hpp"
#include "TextureResource.hpp"

#include "Model.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

class ResourceManager {
public:
  void static Init();
  static ResourceManager *GetInstance();

  ~ResourceManager();

  Model *loadModel(int id);
  Texture *loadTexture(int id);
  Shader *loadShader(int id);

  std::unordered_map<int, ModelResource *> modelResources;
  std::unordered_map<int, TextureResource *> textureResources;
  std::unordered_map<int, ShaderResource *> shaderResources;

  std::unordered_map<int, Model *> loadedModels;
  std::unordered_map<int, Texture *> loadedTextures;
  std::unordered_map<int, Shader *> loadedShaders;

  std::unordered_map<std::string, int> textureTypes;

private:
  static ResourceManager *spInstance;
  ResourceManager();
};
