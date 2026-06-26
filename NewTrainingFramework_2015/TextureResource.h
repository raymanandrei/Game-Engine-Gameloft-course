#pragma once
#include <string>

struct TextureResource
{

	GLuint id;
	std::string file;
	GLenum type;
	GLint min_filter;
	GLint mag_filter;
	GLint wrap_s;
	GLint wrap_t;
};