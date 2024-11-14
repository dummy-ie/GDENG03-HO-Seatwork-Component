#pragma once

#include <unordered_map>
#include <vector>

#include "GameObject.h"

class GameObjectManager
{
private:
	std::unordered_map<std::string, GameObject*> mapGameObjects;
	std::vector<GameObject*> listGameObjects;
	GameObject* selectedObject;

public:
	void createCube();
	void createTexturedCube();
	void createPlane();
	void createQuad();
	void createTeapot();

	void update(float deltaTime);
	void draw(int width, int height);

	std::vector<GameObject*> getAllObjects();
	GameObject* findObjectByName(std::string name);
	void addObject(GameObject* gameObject);
	void deleteObject(GameObject* gameObject);
	void deleteObjectByName(std::string name);
	void deleteAllObjects();
	void setSelectedObject(std::string name);
	void setSelectedObject(GUID guid);
	void setSelectedObject(GameObject* gameObject);
	GameObject* getSelectedObject();

private:
    static GameObjectManager* P_SHARED_INSTANCE;

private:
    GameObjectManager();
	~GameObjectManager();
    GameObjectManager(const GameObjectManager&);
    GameObjectManager& operator = (const GameObjectManager&);

public:
    static GameObjectManager* getInstance();
	static void initialize();
    static void destroy();
};

