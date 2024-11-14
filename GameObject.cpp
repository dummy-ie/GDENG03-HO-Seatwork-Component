#include "GameObject.h"

GameObject::GameObject(std::string name)
{
	HRESULT result = CoCreateGuid(&guid);
	if (!debug::Logger::log(this, result))
		throw std::exception("Game Object GUID creation failed");

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

void GameObject::draw(int width, int height)
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

void GameObject::setName(std::string name)
{
	this->name = name;
}

std::string GameObject::getName()
{
	return this->name;
}

GUID GameObject::getGuid()
{
	return this->guid;
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
