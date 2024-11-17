#pragma once

#include <string>

namespace GDEngine
{
	class GameObject;
	class Component
	{
	public:
		enum ComponentType { NotSet = -1, Script = 0, Renderer = 1, Input = 2, Physics = 3 };

	protected:
		GameObject* m_owner;
		ComponentType m_type;
		std::string m_name;

	public:
		Component(std::string name, ComponentType type, GameObject* owner);
		virtual ~Component();

	public:
		void attachOwner(GameObject* owner);
		void detachOwner();

		GameObject* getOwner();
		ComponentType getType();

		std::string getName();

		virtual void perform(float deltaTime);
	};
}