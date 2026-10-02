#pragma once
#include "SceneObject.hpp"

class Fire : public SceneObject {
public:
  float u_DispMax = 0;
  float u_Time = 0;
  void Update();
  void sendSpecificData();
};
