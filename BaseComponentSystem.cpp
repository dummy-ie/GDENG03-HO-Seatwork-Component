#include "BaseComponentSystem.h"

#include "PhysicsSystem.h"
#include "Logger.h"

BaseComponentSystem* BaseComponentSystem::P_SHARED_INSTANCE = NULL;

PhysicsSystem* BaseComponentSystem::getPhysicsSystem()
{
	return this->physicsSystem;
}

BaseComponentSystem::BaseComponentSystem()
{
	try
	{
		this->physicsSystem = new PhysicsSystem();
	}
	catch (...)
	{
		throw std::exception("PhysicsSystem not created successfully");
	}
	
	debug::Logger::log(P_SHARED_INSTANCE, "Initialized");
}

BaseComponentSystem::~BaseComponentSystem()
{
	delete this->physicsSystem;
	P_SHARED_INSTANCE = nullptr;
	debug::Logger::log(P_SHARED_INSTANCE, "Released");
}

BaseComponentSystem::BaseComponentSystem(const BaseComponentSystem&) {}

BaseComponentSystem* BaseComponentSystem::getInstance()
{
	return P_SHARED_INSTANCE;
}

void BaseComponentSystem::initialize()
{
	if (P_SHARED_INSTANCE)
		throw std::exception("BaseComponentSystem already created");
	P_SHARED_INSTANCE = new BaseComponentSystem();

}

void BaseComponentSystem::destroy()
{
	if (P_SHARED_INSTANCE != NULL)
	{
		delete P_SHARED_INSTANCE;
	}
}
