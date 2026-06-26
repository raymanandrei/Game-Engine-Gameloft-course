#pragma once

#include "../Utilities/utilities.h"

#include "TextureResource.h"

class Texture
{
public:
	Texture();
	~Texture();

	bool Load();

	TextureResource* tr;
	GLuint textureId;
};

