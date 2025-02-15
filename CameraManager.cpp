﻿#include "CameraManager.h"

#include <iostream>

#include "GameObjectManager.h"
#include "Logger.h"
#include "SceneCamera.h"

CameraManager* CameraManager::P_SHARED_INSTANCE = NULL;

Matrix4x4 CameraManager::getMainCameraViewMatrix()
{
	return this->mainCamera->getViewMatrix();
}

Matrix4x4 CameraManager::getMainCameraProjMatrix()
{
	return this->mainCamera->getProjMatrix();
}

Matrix4x4 CameraManager::getSceneCameraViewMatrix()
{
	return this->sceneCamera->getViewMatrix();
}

Matrix4x4 CameraManager::getSceneCameraProjMatrix()
{
	return this->sceneCamera->getProjMatrix();
}

SceneCamera* CameraManager::getSceneCamera()
{
	return this->sceneCamera;
}

SceneCamera* CameraManager::getSceneCameraByIndex(int index)
{
	if (index > sceneCameras.size())
	{
		debug::Logger::log(this, "Camera Index over Cameras in system");
		return NULL;
	}
	return this->sceneCameras[index];
}

std::vector<SceneCamera*> CameraManager::getSceneCameras()
{
	return this->sceneCameras;
}

void CameraManager::setMainCamera(Camera* camera)
{
	mainCamera = camera;
}

void CameraManager::setMainCameraByIndex(int index)
{
	if (index > cameras.size())
	{
		debug::Logger::log(this, "Camera Index over Cameras in system");
		return;
	}
	setMainCamera(cameras[index]);
}

void CameraManager::setSceneCameraProjection(int type)
{
	this->sceneCamera->setProjectionType(type);
}

void CameraManager::updateSceneCamera(float deltaTime)
{
	this->sceneCamera->update(deltaTime);
}

void CameraManager::addCamera(Camera* camera)
{
	if (mainCamera == NULL)
		setMainCamera(camera);
	this->cameras.push_back(camera);
}

void CameraManager::addSceneCamera(SceneCamera* camera)
{
	if (this->sceneCamera == NULL)
		this->sceneCamera = camera;

	this->sceneCameras.push_back(camera);
}

void CameraManager::removeSceneCamera(SceneCamera* camera)
{
	std::string name = camera->getName();
	int index = -1;

	for (int i = 0; i < this->sceneCameras.size() && index == -1; i++)
	{
		if (this->sceneCameras[i] == camera)
			index = i;
	}

	if (index != -1)
	{
		this->sceneCameras.erase(this->sceneCameras.begin() + index);
	}
}

void CameraManager::removeCamera(Camera* camera)
{
	std::string name = camera->getName();
	int index = -1;

	for (int i = 0; i < this->cameras.size() && index == -1; i++)
	{
		if (this->cameras[i] == camera)
			index = i;
	}

	if (index != -1)
	{
		this->cameras.erase(this->cameras.begin() + index);
	}
}

CameraManager::CameraManager()
{
	this->sceneCamera = new SceneCamera("Scene Camera");
	this->sceneCamera->setPosition(0, 1, -8);
	this->sceneCamera->updateViewMatrix();
	this->addCamera(this->sceneCamera);
	debug::Logger::log(this, "Initialized");
}

CameraManager::~CameraManager()
{
	P_SHARED_INSTANCE = nullptr;
	debug::Logger::log(this, "Released");
}

CameraManager::CameraManager(const CameraManager&) {}

CameraManager* CameraManager::getInstance() {
	return P_SHARED_INSTANCE;
}

void CameraManager::initialize()
{
	if (P_SHARED_INSTANCE)
		throw std::exception("Camera manager already created");
	P_SHARED_INSTANCE = new CameraManager();
}

void CameraManager::destroy()
{
	if (P_SHARED_INSTANCE != NULL)
	{
		delete P_SHARED_INSTANCE;
	}
}
