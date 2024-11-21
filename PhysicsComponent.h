#pragma once

#include "AComponent.h"
#include <reactphysics3d/reactphysics3d.h>

namespace GDEngine
{
	using namespace reactphysics3d;
	class PhysicsComponent : public AComponent
	{
	private:
		float m_mass = 1000.0f;
		RigidBody* m_rigidBody;

	public:
		PhysicsComponent(std::string name, AGameObject* owner);
		~PhysicsComponent() override;

	public:
		void perform(float deltaTime) override;
		RigidBody* getRigidBody();
	};
}