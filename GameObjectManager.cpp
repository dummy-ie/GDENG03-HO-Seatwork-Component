#include "GameObjectManager.h"

#include <iostream>

#include "Cube.h"
#include "Plane.h"
#include "Logger.h"
#include "Quad.h"

GameObjectManager* GameObjectManager::P_SHARED_INSTANCE = NULL;

void GameObjectManager::createCube(void* shaderByteCode, size_t sizeShader)
{
	Cube* cube = new Cube("Cube", shaderByteCode, sizeShader);
	this->addObject(cube);
}

void GameObjectManager::createPlane(void* shaderByteCode, size_t sizeShader)
{
	Plane* plane = new Plane("Plane", shaderByteCode, sizeShader);
	this->addObject(plane);
}

void GameObjectManager::createQuad(void* shaderByteCode, size_t sizeShader)
{
	Quad* quad = new Quad("Quad", shaderByteCode, sizeShader);
	this->addObject(quad);
}

void GameObjectManager::update(float deltaTime)
{
	for (GameObject* gameObject : this->listGameObjects)
	{
		if (gameObject->isActive())
			gameObject->update(deltaTime);
	}
}

void GameObjectManager::draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader)
{
	for (GameObject* gameObject : this->listGameObjects)
	{
		if (gameObject->isActive())
			gameObject->draw(window, vertexShader, pixelShader);
	}
}

std::vector<GameObject*> GameObjectManager::getAllObjects()
{
	return this->listGameObjects;
}

GameObject* GameObjectManager::findObjectByName(std::string name)
{
	if (this->mapGameObjects[name] != NULL)
	{
		return this->mapGameObjects[name];
	}
	else
	{
		debug::Logger::error(this, "Object " + name + " is not found");
		return NULL;
	}
}

void GameObjectManager::addObject(GameObject* gameObject)
{
	if (this->mapGameObjects[gameObject->getName()] != NULL)
	{
		int count = 1;
		std::string newName = gameObject->getName() + " " + std::to_string(count);

		while (this->mapGameObjects[newName] != NULL)
		{
			count++;
			newName = gameObject->getName() + " " + std::to_string(count);
		}
		gameObject->name = newName;
		this->mapGameObjects[newName] = gameObject;
	}
	else
	{
		this->mapGameObjects[gameObject->getName()] = gameObject;
	}

	this->listGameObjects.push_back(gameObject);
	gameObject->onCreate();
	debug::Logger::log(gameObject->getName() + " added to hierarchy");
}

void GameObjectManager::deleteObject(GameObject* gameObject)
{
	int index = -1;

	for (int i = 0; i < this->listGameObjects.size() && index == -1; i++)
	{
		if (this->listGameObjects[i] == gameObject)
			index = i;
	}

	if (index != -1)
	{
		this->listGameObjects.erase(this->listGameObjects.begin() + index);
		this->mapGameObjects.erase(this->listGameObjects[index]->getName());

		gameObject->onDestroy();
		delete gameObject;
	}
}

void GameObjectManager::deleteObjectByName(std::string name)
{
	GameObject* object = this->findObjectByName(name);

	if (object != NULL)
	{
		this->deleteObject(object);
	}
}

void GameObjectManager::deleteAllObjects()
{
	if (!this->listGameObjects.empty())
	{
		for (GameObject* gameObject : this->listGameObjects)
			gameObject->onDestroy();
		this->listGameObjects.clear();
		this->mapGameObjects.clear();
	}
}

void GameObjectManager::setSelectedObject(GUID guid)
{
	for (GameObject* object : listGameObjects)
	{
		GUID objectGuid = object->getGuid();
		if (IsEqualGUID(objectGuid, guid))
		{
			this->setSelectedObject(object);
			return;
		}
	}
}

void GameObjectManager::setSelectedObject(std::string name)
{
	if (this->mapGameObjects[name] != NULL)
	{
		this->setSelectedObject(this->mapGameObjects[name]);
	}
}

void GameObjectManager::setSelectedObject(GameObject* gameObject)
{
	this->selectedObject = gameObject;
}

GameObject* GameObjectManager::getSelectedObject()
{
	return this->selectedObject;
}

GameObjectManager::GameObjectManager()
{
	debug::Logger::log(P_SHARED_INSTANCE, "Initialized");
}

GameObjectManager::~GameObjectManager()
{
	this->deleteAllObjects();
	P_SHARED_INSTANCE = nullptr;
	debug::Logger::log(P_SHARED_INSTANCE, "Released");
}

GameObjectManager::GameObjectManager(const GameObjectManager&) {}

GameObjectManager* GameObjectManager::getInstance() {
	return P_SHARED_INSTANCE;
}

void GameObjectManager::initialize()
{
	if (P_SHARED_INSTANCE)
		throw std::exception("Game Object Manager already created");
	P_SHARED_INSTANCE = new GameObjectManager();
	
}

void GameObjectManager::destroy()
{
	if (P_SHARED_INSTANCE != NULL)
	{
		delete P_SHARED_INSTANCE;
	}
}
