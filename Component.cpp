#include "Component.h"

Component::Component(std::string name, ComponentType type, GameObject* owner) : name(name), type(type), owner(owner)
{
}

Component::~Component()
{
	this->owner = nullptr;
	this->type = NotSet;
}

void Component::attachOwner(GameObject* owner)
{
	this->owner = owner;
}

void Component::detachOwner()
{
	this->owner = nullptr;
	delete this;
}

GameObject* Component::getOwner()
{
	return this->owner;
}

Component::ComponentType Component::getType()
{
	return this->type;
}

std::string Component::getName()
{
	return this->name;
}

void Component::perform(float deltaTime)
{
}
