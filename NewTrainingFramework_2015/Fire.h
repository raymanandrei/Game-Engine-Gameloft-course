#pragma once
#include "SceneObject.h"
class Fire : public SceneObject
{
	public:
		float u_DispMax;
		float u_Time;
		void Update();
		void sendSpecificData();
		//Fire();
};

