#include "Camera.hpp"
#include "Ligth.hpp"
#include "sceneObject.hpp"
#include <unordered_map>
#include <vector>

class SceneManager {
public:
  static SceneManager *GetInstance();
  void InitWindow(ESContext *esContext);
  void static Init();
  void Draw(ESContext *esContext);
  void Update(float deltaTime);

  float totalTime;
  Camera camera;
  int screenWidth;
  int screenHeight;

  Vector3 fogColor;
  Vector3 ambientalLigth;
  float smallR = 0;
  float bigR = 0;

  std::vector<SceneObject *> currentSceneObjects;
  std::unordered_map<int, Ligth *> currentSceneLights;

  ~SceneManager();

private:
  SceneManager();
  static SceneManager *spInstance;
};