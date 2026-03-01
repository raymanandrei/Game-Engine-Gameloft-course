#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SceneObject.h"

#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

int Init ( ESContext *esContext )
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	ResourceManager::GetInstance()->Init();
	SceneManager::GetInstance()->Init();
	
	return 0;
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	SceneManager* sceneManager = SceneManager::GetInstance();
	
	switch (key)
	{
		case 'A': case 'a':
			sceneManager->camera.moveOx(-1);
			break;
		case 'D':case'd':
			sceneManager->camera.moveOx(1);
			break;
		case 'W':case 'w':
			sceneManager->camera.moveOz(-1);
			break;
		case 'S': case 's':
			sceneManager->camera.moveOz(1);
			break ;
		case 'Q':case 'q':
			sceneManager->camera.moveOy(1);
			break;
		case 'E': case 'e':
			sceneManager->camera.moveOy(-1);
			break;
		case 'R': case 'r':
			sceneManager->camera.rotateOy(-1);
			break;
		case 'T': case 't':
			sceneManager->camera.rotateOy(1);
			break;
		case 'Y': case 'y':
			sceneManager->camera.rotateOx(-1);
			break;
		case 'U': case 'u':
			sceneManager->camera.rotateOx(1);
			break;
		case 'I': case 'i':
			sceneManager->camera.rotateOz(-1);
			break;
		case 'O': case 'o':
			sceneManager->camera.rotateOz(1);
			break;
		default:
			break;
	}
}

void CleanUp()
{
	SceneManager *sceneManager = SceneManager::GetInstance();
	int objectsSize = sceneManager->currentSceneObjects.size();
	for (int i = 0; i < objectsSize; i++){
		glDeleteBuffers(1, &sceneManager->currentSceneObjects[i]->model->iboId);
		glDeleteBuffers(1, &sceneManager->currentSceneObjects[i]->model->vboId);
	}
}

void Update(ESContext* esContext, float deltaTime) {
	SceneManager::GetInstance()->Update(deltaTime);
}	

void Draw(ESContext* esContext) {
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

