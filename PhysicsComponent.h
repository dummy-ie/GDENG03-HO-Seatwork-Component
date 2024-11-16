#pragma once

#include "Component.h"
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;
class PhysicsComponent : public Component
{
private:
	float mass = 1000.0f;
	RigidBody* rigidBody;

public:
	PhysicsComponent(std::string name, GameObject* owner);
	~PhysicsComponent() override;

public:
	void perform(float deltaTime) override;
	RigidBody* getRigidBody();
};

