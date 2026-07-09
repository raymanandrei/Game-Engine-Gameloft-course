#pragma once

#include "ModelResource.h"

#include "../Utilities/utilities.h"

class Model
{
	public:

		ModelResource* mr;

		GLuint iboId = 0;
		GLuint wiredIboId = 0;
		GLuint vboId = 0;

		int nrIndici = 0;
		int nrIndiciWired = 0;

		Model();
		~Model();

		bool generateModel();

		bool Load();
	
};

