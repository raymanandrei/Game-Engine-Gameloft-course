#pragma once
#include "SceneObject.hpp"

class Ligth {
public:
  int objectId = -1;
  Vector3 position;
  Vector3 direction;
  Vector3 specColor;
  Vector3 diffColor;
  float specPower = 0;
};
