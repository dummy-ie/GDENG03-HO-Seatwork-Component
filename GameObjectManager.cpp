#include "GameObjectManager.h"

#include <iostream>

#include "Logger.h"

GameObjectManager* GameObjectManager::P_SHARED_INSTANCE = NULL;

void GameObjectManager::update(float deltaTime)
{
	for (GameObject* gameObject : this->gameObjects)
	{
		if (gameObject->isActive())
			gameObject->update(deltaTime);
	}
}

void GameObjectManager::draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader)
{
	for (GameObject* gameObject : this->gameObjects)
	{
		if (gameObject->isActive())
			gameObject->draw(window, vertexShader, pixelShader);
	}
}

void GameObjectManager::addObject(GameObject* gameObject)
{
	this->mapGameObject[gameObject->getName()] = gameObject;
	this->gameObjects.push_back(gameObject);
	gameObject->onCreate();
	debug::Logger::log(gameObject->getName() + " added to hierarchy");
}

void GameObjectManager::deleteObject(GameObject* gameObject)
{
	std::string name = gameObject->getName();
	int index = -1;

	for (int i = 0; i < this->gameObjects.size() && index == -1; i++)
	{
		if (this->gameObjects[i] == gameObject)
			index = i;
	}

	if (index != -1)
	{
		this->gameObjects.erase(this->gameObjects.begin() + index);
		this->mapGameObject.erase(this->gameObjects[index]->getName());
		gameObject->onDestroy();
		delete gameObject;
	}
}

void GameObjectManager::deleteLastObject()
{
	if (!gameObjects.empty())
	{
		gameObjects.back()->onDestroy();
		delete gameObjects.back();
		gameObjects.pop_back();
	}
}

void GameObjectManager::deleteAllObjects()
{
	if (!this->gameObjects.empty())
	{
		for (GameObject* gameObject : this->gameObjects)
			gameObject->onDestroy();
		this->gameObjects.clear();
		this->mapGameObject.clear();
	}
}

GameObjectManager::GameObjectManager() {}
GameObjectManager::GameObjectManager(const GameObjectManager&) {}

GameObjectManager* GameObjectManager::getInstance() {
	if (P_SHARED_INSTANCE == NULL)
	{
		P_SHARED_INSTANCE = new GameObjectManager();
		debug::Logger::log(P_SHARED_INSTANCE, "Initialized");
	}

	return P_SHARED_INSTANCE;
}

void GameObjectManager::destroy()
{
	if (P_SHARED_INSTANCE != NULL)
	{
		debug::Logger::log(P_SHARED_INSTANCE, "Released");
		P_SHARED_INSTANCE->deleteAllObjects();
		delete P_SHARED_INSTANCE;
	}
}