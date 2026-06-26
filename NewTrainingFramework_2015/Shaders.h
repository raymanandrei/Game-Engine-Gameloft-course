#pragma once
#include "../Utilities/utilities.h"
class Shaders 
{
public:
	GLuint program, vertexShader, fragmentShader;
	char fileVS[260];
	char fileFS[260];
	GLint positionAttribute;
	GLint colorAttribute;
	GLint matrixUniform;
	GLint matrixCamera;
	GLint textureUniform;
	GLint uvAttribute;
	int Init(char * fileVertexShader, char * fileFragmentShader);
	~Shaders();
};