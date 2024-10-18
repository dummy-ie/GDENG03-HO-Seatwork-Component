#include "SceneCameraHandler.h"

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
