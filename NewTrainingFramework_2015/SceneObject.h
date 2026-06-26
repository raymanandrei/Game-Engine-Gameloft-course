#pragma once
#include <vector>
#include "../Utilities/utilities.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"

class SceneObject {
public:
	GLuint id;
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
	Vector3 color;
	Vector3 followingCamera;

	Model* model;
	Shader* shader;
	std::vector<Texture*> texture;

	int depthTest;

	SceneObject();
	~SceneObject();
	virtual void Draw(ESContext* esContext);
	virtual void sendCommonData();
	virtual void sendSpecificData();
	virtual void Update();	
};

