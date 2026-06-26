#include <vector>
#include <unordered_map>
#include "Camera.h"
#include "sceneObject.h"
#include "Ligth.h"

class SceneManager {
	public:
		static SceneManager* GetInstance();
		void InitWindow(ESContext* esContext);
		void static Init();
		void Draw(ESContext* esContext);
		void Update(float deltaTime);
		
		float totalTime;
		Camera camera;

		Vector3 fogColor;
		Vector3 ambientalLigth;
		float smallR;
		float bigR;

		std::vector<SceneObject*> currentSceneObjects;
		std::unordered_map<int, Ligth*>currentSceneLights;

		~SceneManager();
	private:
		SceneManager();
		static SceneManager* spInstance;
};