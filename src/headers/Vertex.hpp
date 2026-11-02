#include "../Utilities/utilities.hpp"

#ifndef VERTEX_HPP
#define VERTEX_HPP

struct Vertex {
  Vector3 pos;
  Vector3 color;
  Vector3 norm;
  Vector3 binorm;
  Vector3 tgt;
  Vector2 uv;
  Vector2 uv2;
};

#endif
