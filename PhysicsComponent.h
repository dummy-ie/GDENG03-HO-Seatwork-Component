#pragma once

#include "Component.h"
#include <reactphysics3d/reactphysics3d.h>

namespace GDEngine
{
	using namespace reactphysics3d;
	class PhysicsComponent : public Component
	{
	private:
		float m_mass = 1000.0f;
		RigidBody* m_rigidBody;

	public:
		PhysicsComponent(std::string name, GameObject* owner);
		~PhysicsComponent() override;

	public:
		void perform(float deltaTime) override;
		RigidBody* getRigidBody();
	};
}