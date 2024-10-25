#include "GameObject.h"

#include <iostream>

#include "Logger.h"

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
	//debug::Logger::log(name + " position set to : " + localPosition.toString());
}

void GameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
	//debug::Logger::log(name + " position set to : " + localPosition.toString());

}

Vector3D GameObject::getLocalPosition()
{
	return this->localPosition;
}

void GameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
	//debug::Logger::log(name + " scale set to : " + localScale.toString());
}

void GameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
	//debug::Logger::log(name + " scale set to : " + localScale.toString());
}

Vector3D GameObject::getLocalScale()
{
	return this->localScale;
}

void GameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
	//debug::Logger::log(name + " rotation set to : " + localRotation.toString());
}

void GameObject::setRotation(Vector3D rotation)
{
	this->localRotation = rotation;
	//debug::Logger::log(name + " rotation set to : " + localRotation.toString());
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

bool GameObject::isActive()
{
	return this->active;

}

void GameObject::setActive(bool active)
{
	this->active = active;
	//debug::Logger::log(name + " is active set to : " + (this->active ? "true" : "false"));
}

void GameObject::onDestroy()
{
}
