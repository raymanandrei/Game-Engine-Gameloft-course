#include "stdafx.h"
#include <iostream>
#include <ctime>
#include "Fire.h"

void Fire::Update() {
    float currentTime = (float)clock() / CLOCKS_PER_SEC;

	this->u_Time = currentTime * 0.5f;
}

void Fire::sendSpecificData() {
	if (this->shader->sr->U_Time != -1){ 
		glUniform1f(this->shader->sr->U_Time,this->u_Time);
	}

	if (this->shader->sr->U_DispMax != -1) {
		glUniform1f(this->shader->sr->U_DispMax, this->u_DispMax);
	}
}