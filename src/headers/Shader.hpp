#pragma once
#include "../Utilities/utilities.hpp"
#include "ShaderResource.hpp"

class Shader {
public:
  Shader();
  ~Shader();

  bool Load();

  ShaderResource *sr;
  GLuint programId;
};
