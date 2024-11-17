#include "Component.h"

using namespace GDEngine;

Component::Component(std::string name, ComponentType type, GameObject* owner) : m_name(name), m_type(type), m_owner(owner)
{
}

Component::~Component()
{
	this->m_owner = nullptr;
	this->m_type = NotSet;
}

void Component::attachOwner(GameObject* owner)
{
	this->m_owner = owner;
}

void Component::detachOwner()
{
	this->m_owner = nullptr;
	delete this;
}

GameObject* Component::getOwner()
{
	return this->m_owner;
}

Component::ComponentType Component::getType()
{
	return this->m_type;
}

std::string Component::getName()
{
	return this->m_name;
}

void Component::perform(float deltaTime)
{
}
