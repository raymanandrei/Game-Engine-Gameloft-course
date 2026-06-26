#pragma once
#include "SceneObject.h"
#include "../Utilities/Math.h"
class Terrain : public SceneObject
{
	public:	
		virtual void Update();
		void sendSpecificData();
		Vector2 blendTextureOffset;
		int cellSize;	
		int nrCells;
		Terrain();
};

