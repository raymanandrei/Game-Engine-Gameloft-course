#pragma once
#include "../Utilities/EngineMath.hpp"
#include "SceneObject.hpp"

class Terrain : public SceneObject {
public:
  virtual void Update();
  void sendSpecificData();
  Vector2 blendTextureOffset;
  int cellSize;
  int nrCells;
  Terrain();
};
