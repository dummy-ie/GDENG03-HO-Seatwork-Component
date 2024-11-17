#pragma once

#include <vector>
#include <string>
#include <guiddef.h>

#include "Component.h"

#include "Matrix4x4.h"
#include "Vector3D.h"

#include "Prerequisites.h"

namespace GDEngine {
	typedef Vector4D AQuaternion;

	class GameObject
	{
	private:
		typedef std::vector<Component*> ComponentList;

	protected:
		GUID m_guid;
		std::string m_name;

		Vector3D m_localPosition;
		Vector3D m_localScale;
		Vector3D m_localRotation;
		AQuaternion m_orientation;
		Matrix4x4 m_localMatrix;

		ComponentList m_componentList;

		friend class GameObjectManager;

	private:
		bool m_active;
		bool m_physics;

	public:
		GameObject(std::string name);
		virtual ~GameObject();

	public:
		virtual void update(float deltaTime) = 0;
		virtual void draw(int width, int height);

	public:
		void setPosition(float x, float y, float z);
		void setPosition(Vector3D position);
		Vector3D getLocalPosition();

		void setScale(float x, float y, float z);
		void setScale(Vector3D scale);
		Vector3D getLocalScale();

		void setRotation(float x, float y, float z);
		void setRotation(Vector3D rotation);
		void setOrientation(AQuaternion orientation);
		Vector3D getLocalRotation();

		void setName(std::string name);
		std::string getName();
		GUID getGuid();

		void updateLocalMatrix();
		void setLocalMatrix(float matrix[16]);
		void setLocalMatrix(Vector3D position, AQuaternion orientation, float matrix[16]);
		float* getLocalMatrix();
		float* getPhysicsLocalMatrix();

		bool isActive();
		void setActive(bool active);

		bool isPhysics();
		void setPhysics(bool physics);

		void attachComponent(Component* component);
		void detachComponent(Component* component);

		Component* findComponentByName(std::string name);
		Component* findComponentOfType(Component::ComponentType type, std::string name);
		ComponentList getComponentsOfType(Component::ComponentType type);
		ComponentList getComponentsOfTypeRecursive(Component::ComponentType type);


		__declspec(align(16))
			struct CBObjectData
		{
			Matrix4x4 worldMatrix;
			float time;
		};

	protected:
		struct vertex
		{
			Vector3D position;
			Vector3D color;
			Vector3D color2;
		};

	public:
		virtual void onCreate();
		virtual void onDestroy();
	};
}