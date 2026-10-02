#pragma once

#include "../Utilities/utilities.hpp"

#include "TextureResource.hpp"

class Texture {
public:
  Texture();
  ~Texture();

  bool Load();

  TextureResource *tr;
  GLuint textureId;
};
