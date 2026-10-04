#include "SceneManager.hpp"
#include "../Utilities/pugixml-1.16/pugixml.hpp"
#include "Camera.hpp"
#include "Fire.hpp"
#include "Ligth.hpp"
#include "ResourceManager.hpp"
#include "SceneObject.hpp"
#include "SkyBox.hpp"
#include "Terrain.hpp"
#include "XML.hpp"
#include "stdafx.hpp"
#include <fstream>
#include <iostream>
#include <vector>

SceneManager *SceneManager::spInstance = nullptr;

SceneManager *SceneManager::GetInstance() {
  if (spInstance == nullptr)
    spInstance = new SceneManager();
  return spInstance;
}

SceneManager::SceneManager() {
  std::cout << "Created SceneManger object\n";
}

SceneManager::~SceneManager() {
  delete spInstance;
}

void SceneManager::Update(float deltaTime) {
  totalTime += deltaTime;
  if (totalTime >= 0.008) {
    camera.setDeltaTime(totalTime);
    totalTime = 0;
  }
}

void SceneManager::InitWindow(ESContext *esContext) {
  printf("Init windows function start\n");

  char *xmlPath = "sceneManager.xml";

  pugi::xml_document doc;
  pugi::xml_parse_result xmlFile = doc.load_file(xmlPath);

  if (!xmlFile) {
    std::cout << "sceneManger XML not Found (InitWindow)\n";
  }

  pugi::xml_node root = doc.child("sceneManager");
  pugi::xml_node gameName = root.child("gameName");
  pugi::xml_node defaultScreenSize = root.child("defaultScreenSize");

  // std::cout << defaultScreenSize.child_value("width") << "\n";

  screenWidth = std::stoi(defaultScreenSize.child_value("width"));
  screenHeight = std::stoi(defaultScreenSize.child_value("height"));

  esCreateWindow(esContext, gameName.value(), screenWidth, screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

  printf("Window created\n");
}

void SceneManager::Init() {

  std::cout << "SceneManager::Init() start\n";

  char *xmlPath = "sceneManager.xml";

  pugi::xml_document doc;
  pugi::xml_parse_result xmlFile = doc.load_file(xmlPath);

  if (!xmlFile) {
    std::cout << "sceneManger XML not Found (SceneManager::Init())\n";
  }

  pugi::xml_node root = doc.child("sceneManager");
  pugi::xml_node backgroundColor = root.child("backgroundColor");
  pugi::xml_node controls = root.child("controls");
  pugi::xml_node fog = root.child("fog");
  pugi::xml_node ligths = root.child("ligths");

  if (fog) {
    SceneManager::spInstance->smallR = std::stof(fog.child_value("r"));
    SceneManager::spInstance->bigR = std::stof(fog.child_value("R"));
    pugi::xml_node color = fog.child("color");
    if (color) {
      readVector3ColorFromXml(SceneManager::spInstance->fogColor, color);
    }
  }

  if (ligths) {
    pugi::xml_node ambientalLigth = ligths.child("ambientalLigth");
    if (ambientalLigth) {
      readVector3ColorFromXml(SceneManager::GetInstance()->ambientalLigth, ambientalLigth);
    }

    for (pugi::xml_node ligth = ligths.child("ligth"); ligth; ligth = ligth.next_sibling("ligth")) {
      Ligth *newLigth = new Ligth();
      int id = std::stoi(ligth.first_attribute().value());
      std::cout << "Ligth id: " << id << '\n';
      if (ligth.child("position")) {
        readVector3XYZFromXml(newLigth->position, ligth.child("position"));
      }
      if (ligth.child("specColor")) {
        readVector3ColorFromXml(newLigth->specColor, ligth.child("specColor"));
      }
      if (ligth.child("diffColor")) {
        readVector3ColorFromXml(newLigth->diffColor, ligth.child("diffColor"));
      }
      if (ligth.child("specPower")) {
        newLigth->specPower = std::stof(ligth.child_value("specPower"));
      }
      SceneManager::GetInstance()->currentSceneLights.insert({id, newLigth});
    }
  }

  pugi::xml_node objects = root.child("objects");

  for (pugi::xml_node object = objects.child("object"); object; object = object.next_sibling("object")) {

    SceneObject *newObject = new SceneObject();
    std::string type = object.child_value("type");
    std::string name = object.child_value("name");
    std::cout << name << "\n";
    std::cout << type << std::endl;
    if (type == "terrain") {
      newObject = new Terrain();
      if (object.child("inaltimi")) {
        readVector3ColorFromXml(newObject->color, object.child("inaltimi"));
      }
    } else if (type == "skyBox") {
      newObject = new SkyBox();
    } else if (type == "fire") {
      newObject = new Fire();
      Fire *fireObj = static_cast<Fire *>(newObject);
      if (fireObj) {
        fireObj->u_DispMax = std::stof(object.child_value("u_DispMax"));
      }
    }

    newObject->id = std::stoi(object.first_attribute().value());

    if (object.child("position")) {
      readVector3XYZFromXml(newObject->position, object.child("position"));
    }

    if (object.child("rotation")) {
      readVector3XYZFromXml(newObject->rotation, object.child("rotation"));
    }

    if (object.child("scale")) {
      readVector3XYZFromXml(newObject->scale, object.child("scale"));
    }

    if (object.child("color")) {
      readVector3ColorFromXml(newObject->color, object.child("color"));
    }

    pugi::xml_node followingCamera = object.child("followingCamera");

    if (followingCamera) {
      if (followingCamera.child("ox"))
        newObject->followingCamera.x = 1;
      if (followingCamera.child("oy"))
        newObject->followingCamera.y = 1;
      if (followingCamera.child("oz"))
        newObject->followingCamera.z = 1;
    }

    ResourceManager *resourceManager = ResourceManager::GetInstance();

    int modelId = -1;
    std::string modelStringId = object.child_value("model");
    if (modelStringId != "generated") {
      std::cout << object.child_value("model") << std::endl;
      modelId = std::stoi(object.child_value("model"));
    } else {
      std::cout << type << std::endl;
      newObject->model = new Model();
      newObject->model->generateModel();
    }

    pugi::xml_node textureRoot = object.child("textures");
    int textureId = -1;
    if (textureRoot) {
      pugi::xml_node textureNode = textureRoot.child("texture");
      pugi::xml_attribute idAttr = textureNode.attribute("id");
      for (pugi::xml_node textures = textureRoot.child("texture"); textures;
           textures = textures.next_sibling("texture")) {
        pugi::xml_attribute idAttr = textures.attribute("id");
        textureId = std::stoi(idAttr.value());
        std::cout << "TextureID :: " << textureId << '\n';
        std::cout << resourceManager->textureResources[textureId]->file << std::endl;
        Texture *text = resourceManager->loadTexture(textureId);
        if (text->tr)
          newObject->texture.push_back(text);
      }
    }

    int shaderId = -1;
    shaderId = std::stoi(object.child_value("shader"));

    if (modelId != -1) {
      newObject->model = resourceManager->loadModel(modelId);
    }

    if (shaderId != -1) {
      newObject->shader = resourceManager->loadShader(shaderId);
    }

    SceneManager::spInstance->currentSceneObjects.push_back(newObject);
  }

  std::cout << "SceneManager::Init() end\n";
}

void SceneManager::Draw(ESContext *esContext) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glDisable(GL_CULL_FACE);

  for (SceneObject *object : currentSceneObjects) {
    object->Draw(esContext);
    object->Update();
  }

  eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}