#pragma once

#include "ModelResource.h"

#include "../Utilities/utilities.h"

class Model
{
	public:

		ModelResource* mr;

		GLuint iboId;
		GLuint wiredIboId;
		GLuint vboId;

		int nrIndici;
		int nrIndiciWired;

		Model();
		~Model();

		bool generateModel();

		bool Load();
	
};

