#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SceneObject.h"

#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

int static Init ( ESContext *esContext )
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Read all resources from xml
	ResourceManager::GetInstance()->Init();

	//Init Scene
	SceneManager::GetInstance()->Init();

	SceneManager::GetInstance()->camera.setDeltaTime(0.008f);
	
	return 0;
}

void static Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	//Get scene Camera
	Camera *camera = &SceneManager::GetInstance()->camera;

	switch (key)
	{
		case 'A': case 'a':
			camera->moveOx(-1);
			break;
		case 'D':case'd':
			camera->moveOx(1);
			break;
		case 'W':case 'w':
			camera->moveOz(-1);
			break;
		case 'S': case 's':
			camera->moveOz(1);
			break ;
		case 'Q':case 'q':
			camera->moveOy(1);
			break;
		case 'E': case 'e':
			camera->moveOy(-1);
			break;
		case 'R': case 'r':
			camera->rotateOy(-1);
			break;
		case 'T': case 't':
			camera->rotateOy(1);
			break;
		case 'Y': case 'y':
			camera->rotateOx(-1);
			break;
		case 'U': case 'u':
			camera->rotateOx(1);
			break;
		case 'I': case 'i':
			camera->rotateOz(-1);
			break;
		case 'O': case 'o':
			camera->rotateOz(1);
			break;
		default:
			break;
	}
}

void static CleanUp()
{
	SceneManager *sceneManager = SceneManager::GetInstance();
	int objectsSize = sceneManager->currentSceneObjects.size();
	for (int i = 0; i < objectsSize; i++){
		glDeleteBuffers(1, &sceneManager->currentSceneObjects[i]->model->iboId);
		glDeleteBuffers(1, &sceneManager->currentSceneObjects[i]->model->vboId);
	}
}

void static Update(ESContext* esContext, float deltaTime) {
	SceneManager::GetInstance()->Update(deltaTime);
}	

void static Draw(ESContext* esContext) {
	SceneManager::GetInstance()->Draw(esContext);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext;

    esInitContext ( &esContext );

	SceneManager::GetInstance()->InitWindow(&esContext);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw);
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();

	printf("Press any key...\n");
	_getch();

	return 0;
}

