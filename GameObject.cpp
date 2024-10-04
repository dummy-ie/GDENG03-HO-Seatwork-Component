#include "GameObject.h"

GameObject::GameObject(vec3 position, vec3 scale)
{
	this->position = position;
	this->scale = scale;
}

GameObject::~GameObject()
{
}

void GameObject::onCreate()
{
}

void GameObject::update()
{
}

void GameObject::draw()
{
}

void GameObject::setPosition(vec3 position)
{
	this->position = position;
}

void GameObject::setScale(vec3 scale)
{
	this->scale = scale;
}

void GameObject::onDestroy()
{
}
