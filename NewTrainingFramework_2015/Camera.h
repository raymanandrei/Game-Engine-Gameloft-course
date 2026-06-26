#pragma once
#include "../Utilities/Math.h"
class Camera
{
	public:

		Vector3 position;
		Vector3 target;
		Vector3 up;
		GLfloat moveSpeed;
		GLfloat rotateSpeed;
		GLfloat nearPlane;
		GLfloat farPlane;
		GLfloat fov;
		GLfloat deltaTime;
		Vector3 xAxis;
		Vector3 yAxis;
		Vector3 zAxis;

		Matrix viewMatrix;
		Matrix worldMatrix;
		Matrix perspectiveMatrix;

		Camera();
		~Camera();

		void moveOx(GLfloat sens);

		void moveOy(GLfloat sens);

		void moveOz(GLfloat sens);

		void rotateOx(GLfloat sens);

		void rotateOy(GLfloat sens);

		void rotateOz(GLfloat sens);
	
		void updateAxes();

		void updateWorldView();

		void setDeltaTime(GLfloat);
};