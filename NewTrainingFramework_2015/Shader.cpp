#include "stdafx.h"
#include "Shader.h"

#include "../Utilities/utilities.h"

Shader::Shader() {
}

Shader::~Shader() {
}

bool Shader::Load() {
	//printf("Loading shader with vertex shader: %s and fragment shader: %s\n", sr->vs.c_str(), sr->fs.c_str());
	GLuint vertexShader = esLoadShader(GL_VERTEX_SHADER, (char*)(sr->vs).c_str());

	if (vertexShader == 0)
		return -1;

	GLuint fragmentShader = esLoadShader(GL_FRAGMENT_SHADER,(char *)(sr->fs).c_str());

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return -2;
	}

	programId = esLoadProgram(vertexShader, fragmentShader);

	sr->positionAttribute = glGetAttribLocation(programId, "a_posL");
	sr->colorAttribute = glGetAttribLocation(programId, "a_color");
	sr->objectColor = glGetUniformLocation(programId, "objectColor");
	sr->matrixCamera = glGetUniformLocation(programId, "MVP");
	sr->a_norm = glGetAttribLocation(programId, "a_norm");
	for (int i = 0; i < 5; i++) {
		std::string con = "u_texture_" + std::to_string(i);
		sr->textureUniform[i] = glGetUniformLocation(programId,(char * )con.c_str());
	}
	sr->uvAttribute = glGetAttribLocation(programId, "a_uv");
	sr->uv2Attribute = glGetAttribLocation(programId, "a_uv2");
	sr->blendTextureOffset = glGetUniformLocation(programId, "blendTextureOffset");
	sr->smallR = glGetUniformLocation(programId, "smallR");
	sr->bigR = glGetUniformLocation(programId, "bigR");
	sr->fogColor = glGetUniformLocation(programId, "fogColor");
	sr->cameraPosition = glGetUniformLocation(programId, "cameraPosition");
	sr->matrixModel = glGetUniformLocation(programId, "matrixModel");
	sr->U_Time = glGetUniformLocation(programId, "U_Time");
	sr->U_DispMax = glGetUniformLocation(programId, "U_DispMax");

	sr->lightPosition = glGetUniformLocation(programId, "lightPosition");
	sr->SpecPower = glGetUniformLocation(programId, "SpecPower");
	sr->c_lightDiff = glGetUniformLocation(programId, "c_lightDiff");
	sr->c_lightSpec = glGetUniformLocation(programId, "c_lightSpec");
	sr->c_amb = glGetUniformLocation(programId, "c_amb");
	return true;
}