#include "GameObject.h"

GameObject::GameObject(vec3 position, vec3 scale, vec3 color)
{
	this->position = position;
	this->scale = scale;
	this->color = color;
}

GameObject::~GameObject()
{
}

void GameObject::onCreate()
{
}

void GameObject::update(float deltaTime)
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

void GameObject::setColor(vec3 color)
{
	this->color = color;
}

void GameObject::onDestroy()
{
}
