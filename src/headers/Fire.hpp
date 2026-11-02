#include "SceneObject.hpp"

#ifndef FIRE_HPP
#define FIRE_HPP

class Fire : public SceneObject {
public:
  float u_DispMax = 0;
  float u_Time = 0;
  void Update();
  void sendSpecificData();
};

#endif
