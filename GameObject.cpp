#include "GameObject.h"

GameObject::GameObject(Vector3D position, Vector3D scale)
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

void GameObject::update(float deltaTime)
{
}

void GameObject::draw(ConstantBuffer* cb)
{
}

void GameObject::setPosition(Vector3D position)
{
	this->position = position;
}

void GameObject::setScale(Vector3D scale)
{
	this->scale = scale;
}

void GameObject::onDestroy()
{
}
