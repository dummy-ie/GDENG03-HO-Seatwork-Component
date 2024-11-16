#include "PhysicsSystem.h"

#include "EngineTime.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "Logger.h"

PhysicsSystem::PhysicsSystem()
{
	this->physicsCommon = new PhysicsCommon();

	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = Vector3(0, -9.81, 0);

	this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);

	debug::Logger::log(this, "Created Physics World");
	debug::Logger::log(this, "Initialize");
}

PhysicsSystem::~PhysicsSystem()
{
	delete this->physicsCommon;
}

void PhysicsSystem::registerComponent(PhysicsComponent* component)
{
	this->mapComponents[component->getName()] = component;
	this->listComponents.push_back(component);
	debug::Logger::log(component->getName() + " registered Component");
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* component)
{
	if (this->mapComponents[component->getName()] == NULL)
	{
		debug::Logger::log(component->getName() + " not registered in Physics System");
		return;
	}

	int index = -1;

	this->mapComponents.erase(component->getName());
	for (int i = 0; i < this->listComponents.size() && index == -1; i++)
	{
		if (this->listComponents[i] == component)
			index = i;
	}

	if (index != -1)
	{
		this->listComponents.erase(this->listComponents.begin() + index);
	}

	debug::Logger::log("Unregistered " + component->getName());
}

void PhysicsSystem::unregisterComponentByName(std::string name)
{
	if (this->mapComponents[name] != NULL)
	{
		this->unregisterComponent(this->mapComponents[name]);
	}
}

PhysicsComponent* PhysicsSystem::findComponentByName(std::string name)
{
	if (this->mapComponents[name] == NULL)
		debug::Logger::error(this, "Component " + name + " is not found");

	return this->mapComponents[name];
}

std::vector<PhysicsComponent*> PhysicsSystem::getAllComponents()
{
	return this->listComponents;
}

void PhysicsSystem::updateAllComponents()
{
	if (EngineTime::getDeltaTime() > 0.0f)
	{
		this->physicsWorld->update(EngineTime::getDeltaTime());
		for (int i = 0; i < this->listComponents.size(); i++)
		{
			if (listComponents[i]->getOwner()->isActive())
				this->listComponents[i]->perform(EngineTime::getDeltaTime());
		}
	}
}

PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
	return this->physicsWorld;
}

PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
	return this->physicsCommon;
}