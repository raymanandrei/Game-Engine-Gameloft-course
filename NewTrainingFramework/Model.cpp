#include "stdafx.h"
#include <iostream>
#include <vector>
#include "Model.h"
#include "Vertex.h"
#include "ReadNFG.h"

#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

Model::Model() {
}

Model::~Model() {
}

bool Model::Load() {
	glGenBuffers(1, &iboId);
	glGenBuffers(1, &vboId);

	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;
	readNfg(mr->file,vertices,indices);

	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].color.x = 1.0f;
		vertices[i].color.y = 0.0f;
		vertices[i].color.z = 1.0f;
	}

	nrIndici = indices.size();
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}	

bool Model::generateModel() {
	int n = 4;
	int d = 500;
	std::vector<Vertex>vertices;
	std::vector<unsigned short> indices;

	//this->mr->id.assign("terrain");
	this->mr = new ModelResource();
	this->mr->id = "terrain";


	for (float i = (-n / 2) * d; i <= (n / 2) * d; i+=d) {
		for (float j = (-n / 2) * d; j <= (n / 2) * d; j+=d) {
			Vertex v;
			v.pos.x = j;
			v.pos.y = -70.0f;
			v.pos.z = i ;

			v.uv.x = j;
			v.uv.y = i;

			v.uv2.x = j / n;
			v.uv2.y = i / n;

			vertices.push_back(v);
		}
	}

	for (int i = 0;i < n;i++){
		for (int j = 0; j < n; j++) {
			int topLeft = i * (n + 1) + j;
			int topRight = topLeft + 1;
			int bottomLeft = (i + 1) * (n + 1) + j;
			int bottomRight = bottomLeft + 1;

			indices.push_back(topLeft);
			indices.push_back(topRight);
			indices.push_back(bottomLeft);	

			indices.push_back(topRight);
			indices.push_back(bottomRight);
			indices.push_back(bottomLeft);
		}
	}

	nrIndici = indices.size();

	glGenBuffers(1, &iboId);
	glGenBuffers(1, &vboId);
	
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}