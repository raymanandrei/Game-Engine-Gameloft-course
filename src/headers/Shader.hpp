#include "../Utilities/utilities.hpp"
#include "ShaderResource.hpp"

#ifndef SHADER_HPP
#define SHADER_HPP

class Shader {
public:
  Shader();
  ~Shader();

  bool Load();

  ShaderResource *sr;
  GLuint programId;
};

#endif
