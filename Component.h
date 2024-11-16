#pragma once

#include <string>

class GameObject;
class Component
{
public:
	enum ComponentType { NotSet = -1, Script = 0, Renderer = 1, Input = 2, Physics = 3};

protected:
	GameObject* owner;
	ComponentType type;
	std::string name;

public:
	Component(std::string name, ComponentType type, GameObject* owner);
	virtual ~Component();

public:
	void attachOwner(GameObject* owner);
	void detachOwner();

	GameObject* getOwner();
	ComponentType getType();

	std::string getName();

	virtual void perform(float deltaTime);
};

