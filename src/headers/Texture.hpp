#include "../Utilities/utilities.hpp"

#include "TextureResource.hpp"

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture {
public:
  Texture();
  ~Texture();

  bool Load();

  TextureResource *tr;
  GLuint textureId;
};

#endif
