#include "SceneCameraHandler.h"

#include <iostream>

#include "CameraManager.h"
#include "GameObjectManager.h"

SceneCameraHandler* SceneCameraHandler::P_SHARED_INSTANCE = NULL;

Matrix4x4 SceneCameraHandler::getSceneCameraViewMatrix()
{
	return this->sceneCamera->getViewMatrix();
}

SceneCameraHandler::SceneCameraHandler()
{
	this->sceneCamera = new SceneCamera("Scene Camera");
	this->sceneCamera->setPosition(0, 0, -5);
	this->sceneCamera->updateViewMatrix();
	Vector3D position = sceneCamera->getLocalPosition();
	std::cout << "Scene Camera Initialized at Position : (" << position.x << ", " << position.y << ", " << position.z << ")" << std::endl;
	GameObjectManager::getInstance()->addObject(sceneCamera);
	CameraManager::getInstance()->addCamera(sceneCamera);
}

SceneCameraHandler::SceneCameraHandler(const SceneCameraHandler&) {}

SceneCameraHandler* SceneCameraHandler::getInstance()
{
	return P_SHARED_INSTANCE;
}

void SceneCameraHandler::initialize()
{
	P_SHARED_INSTANCE = new SceneCameraHandler();
}

void SceneCameraHandler::destroy()
{
	delete P_SHARED_INSTANCE;
}
