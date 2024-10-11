#include "GameObject.h"

GameObject::GameObject(std::string name)
{
	this->name = name;
	this->localPosition = Vector3D::zero();
	this->localRotation = Vector3D::zero();
	this->localScale = Vector3D::one();
	this->active = true;
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

void GameObject::draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader)
{
}

void GameObject::setPosition(Vector3D position)
{
	this->localPosition = position;
}

void GameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
}

Vector3D GameObject::getLocalPosition()
{
	return this->localPosition;
}

void GameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
}

void GameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
}

Vector3D GameObject::getLocalScale()
{
	return this->localScale;
}

void GameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
}

void GameObject::setRotation(Vector3D rotation)
{
	this->localRotation = rotation;
}

Vector3D GameObject::getLocalRotation()
{
	return this->localRotation;
}

std::string GameObject::getName()
{
	return this->name;
}

bool GameObject::isActive()
{
	return this->active;
}

void GameObject::setActive(bool active)
{
	this->active = active;
}

void GameObject::onDestroy()
{
}
