#pragma once

#include <unordered_map>
#include <vector>

#include "GameObject.h"

class GameObjectManager
{
private:
	std::unordered_map<std::string, GameObject*> mapGameObject;
	std::vector<GameObject*> gameObjects;

public:
	void update(float deltaTime);
	void draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader);

	void addObject(GameObject* gameObject);
	void deleteObject(GameObject* gameObject);
	void deleteLastObject();
	void deleteAllObjects();

private:
    static GameObjectManager* P_SHARED_INSTANCE;

private:
    GameObjectManager();
    GameObjectManager(const GameObjectManager&);
    GameObjectManager& operator = (const GameObjectManager&);

public:
    static GameObjectManager* getInstance();
    static void destroy();
};

