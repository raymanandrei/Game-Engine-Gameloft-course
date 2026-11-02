#include "../Utilities/EngineMath.hpp"
#include "SceneObject.hpp"

#ifndef TERRAIN_HPP
#define TERRAIN_HPP

class Terrain : public SceneObject {
public:
  virtual void Update();
  void sendSpecificData();
  Vector2 blendTextureOffset;
  int cellSize;
  int nrCells;
  Terrain();
};

#endif
