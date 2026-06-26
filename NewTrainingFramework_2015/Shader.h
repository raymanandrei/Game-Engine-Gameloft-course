#pragma once
#include "../Utilities/utilities.h"
#include "ShaderResource.h"

class Shader
{
	public:
		Shader();
		~Shader();

		bool Load();

		ShaderResource *sr;
		GLuint programId;
};
