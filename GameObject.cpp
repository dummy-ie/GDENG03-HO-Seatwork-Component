#include "GameObject.h"

#include "BaseComponentSystem.h"
#include "Logger.h"
#include "PhysicsSystem.h"


using namespace GDEngine;

GameObject::GameObject(std::string name)
{
	HRESULT result = CoCreateGuid(&m_guid);
	if (!Logger::log(this, result)) {
		Logger::throw_exception("Game Object GUID creation failed");
	}

	this->m_name = name;
	this->m_localPosition = Vector3D::zero();
	this->m_localRotation = Vector3D::zero();
	this->m_localScale = Vector3D::one();
	this->m_orientation = Vector4D(0, 0, 0, 1);
	this->m_physics = false;

	this->updateLocalMatrix();

	this->m_active = true;
}

GameObject::~GameObject()
{
	for (Component* component : m_componentList)
	{
		component->detachOwner();
	}
	this->m_componentList.clear();
}

void GameObject::onCreate()
{
}

void GameObject::update(float deltaTime)
{
	Logger::log("Updating Game Object : " + this->m_name);
}

void GameObject::draw(int width, int height)
{
}

void GameObject::setPosition(Vector3D position)
{
	this->m_localPosition = position;
}

void GameObject::setPosition(float x, float y, float z)
{
	this->m_localPosition = Vector3D(x, y, z);

}

Vector3D GameObject::getLocalPosition()
{
	return this->m_localPosition;
}

void GameObject::setScale(float x, float y, float z)
{
	this->m_localScale = Vector3D(x, y, z);
}

void GameObject::setScale(Vector3D scale)
{
	this->m_localScale = scale;
}

Vector3D GameObject::getLocalScale()
{
	return this->m_localScale;
}

void GameObject::setRotation(float x, float y, float z)
{
	this->m_localRotation = Vector3D(x, y, z);
}

void GameObject::setRotation(Vector3D rotation)
{
	this->m_localRotation = rotation;
}

void GameObject::setOrientation(Vector4D orientation)
{
	this->m_orientation = orientation;
}

Vector3D GameObject::getLocalRotation()
{
	return this->m_localRotation;
}

void GameObject::setName(std::string name)
{
	this->m_name = name;
}

std::string GameObject::getName()
{
	return this->m_name;
}

GUID GameObject::getGuid()
{
	return this->m_guid;
}

void GameObject::updateLocalMatrix()
{
	if (!m_physics)
	{
		Matrix4x4 transform, rotation, translate;
		Matrix4x4 temp;

		// Scale
		transform.setIdentity();
		transform.setScale(this->m_localScale);

		// Scale * Rotation
		/*rotation.setIdentity();
		rotation.setRotationZ(this->m_localRotation.z);

		temp.setIdentity();
		temp.setRotationY(this->m_localRotation.y);
		rotation *= temp;

		temp.setIdentity();
		temp.setRotationX(this->m_localRotation.x);
		rotation *= temp;*/

		rotation.setIdentity();
		rotation.setRotation(this->m_orientation);

		// Scale * Rotation * Translation
		translate.setIdentity();
		translate.setTranslation(this->m_localPosition);


		translate *= rotation;
		transform *= translate;

		this->m_localMatrix = transform;
	}
}

void GameObject::setLocalMatrix(float matrix[16])
{
	Matrix4x4 transform, scale, translate, temp;

	/*transform.setIdentity();
	transform.setScale(this->m_localScale);

	temp.setIdentity();
	temp.setMatrix(matrix);

	transform *= temp;
	this->m_localMatrix = transform;*/

	//temp.setIdentity();
	//temp.setTranslation(this->m_localPosition);
	//transform *= temp;

	scale.setIdentity();
	scale.setScale(this->m_localScale);

	translate.setIdentity();
	translate.setTranslation(this->m_localPosition);

	temp.setIdentity();
	temp.setMatrix(matrix);
	//temp.getMatrix();
	//debug::Logger::log(temp.getTranslation().toString());

	translate *= temp;
	//translate.getMatrix();
	scale *= translate;
	transform = scale;

	this->m_localMatrix = transform;

	/*this->m_localPosition = Vector3D(matrix[12], matrix[13], matrix[14]);

	debug::Logger::log("[" + std::to_string(matrix[0]) + "," + std::to_string(matrix[1]) + "," + std::to_string(matrix[2]) + "," + std::to_string(matrix[3]) + "]");
	debug::Logger::log("[" + std::to_string(matrix[4]) + "," + std::to_string(matrix[5]) + "," + std::to_string(matrix[6]) + "," + std::to_string(matrix[7]) + "]");
	debug::Logger::log("[" + std::to_string(matrix[8]) + "," + std::to_string(matrix[9]) + "," + std::to_string(matrix[10]) + "," + std::to_string(matrix[11]) + "]");
	debug::Logger::log("[" + std::to_string(matrix[12]) + "," + std::to_string(matrix[13]) + "," + std::to_string(matrix[14]) + "," + std::to_string(matrix[15]) + "]");

	//matrix[12] = 0;
	//matrix[13] = 0;
	//matrix[14] = 0;

	scale.setIdentity();
	scale.setScale(this->m_localScale);

	/*temp.setIdentity();
	temp.setMatrix(matrix);

	temp.getMatrix();

	Matrix4x4 rotate;
	rotate.setIdentity();
	rotate.setRotation(m_orientation);
	rotate.transpose();
	rotate.getMatrix();

	translate.setIdentity();
	translate.setTranslation(this->m_localPosition);

	/*debug::Logger::log("[" + std::to_string(m_mat[0]) + "," + std::to_string(m_mat[1]) + "," + std::to_string(m_mat[2]) + "," + std::to_string(m_mat[3]) + "]");
	debug::Logger::log("[" + std::to_string(m_mat[4]) + "," + std::to_string(m_mat[5]) + "," + std::to_string(m_mat[6]) + "," + std::to_string(m_mat[7]) + "]");
	debug::Logger::log("[" + std::to_string(m_mat[8]) + "," + std::to_string(m_mat[9]) + "," + std::to_string(m_mat[10]) + "," + std::to_string(m_mat[11]) + "]");
	debug::Logger::log("[" + std::to_string(m_mat[12]) + "," + std::to_string(m_mat[13]) + "," + std::to_string(m_mat[14]) + "," + std::to_string(m_mat[15]) + "]");

	translate *= rotate;
	translate.getMatrix();
	scale *= translate;
	transform = scale;

	this->m_localMatrix = transform;*/
	//this->m_localPosition = this->m_localMatrix.getTranslation();
}

void GameObject::setLocalMatrix(Vector3D position, Vector4D orientation, float matrix[16])
{
	Matrix4x4 transform, scale, translate, temp;

	this->m_localPosition = position;
	this->m_orientation = orientation;

	scale.setIdentity();
	scale.setScale(this->m_localScale);

	temp.setIdentity();
	temp.setMatrix(matrix);

	//translate *= temp;
	scale *= temp;
	transform = scale;

	this->m_localMatrix = transform;
}

float* GameObject::getLocalMatrix()
{
	return this->m_localMatrix.getMatrix();
}


float* GameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 transform, rotation;
	Matrix4x4 temp;

	// Scale
	transform.setIdentity();
	transform.setScale(Vector3D::one());

	// Scale * Rotation
	rotation.setIdentity();
	rotation.setRotationZ(this->m_localRotation.z);

	temp.setIdentity();
	temp.setRotationY(this->m_localRotation.y);
	rotation *= temp;

	temp.setIdentity();
	temp.setRotationX(this->m_localRotation.x);
	rotation *= temp;

	transform *= rotation;
	// Scale * Rotation * Translation
	temp.setIdentity();
	temp.setTranslation(this->m_localPosition);
	transform *= temp;

	return transform.getMatrix();
}

bool GameObject::isActive()
{
	return this->m_active;

}

void GameObject::setActive(bool active)
{
	this->m_active = active;
}

bool GameObject::isPhysics()
{
	return this->m_physics;
}

void GameObject::setPhysics(bool physics)
{
	this->m_physics = physics;
}

void GameObject::attachComponent(Component* component)
{
	this->m_componentList.push_back(component);
	component->attachOwner(this);
}

void GameObject::detachComponent(Component* component)
{
	int index = -1;

	for (int i = 0; i < this->m_componentList.size() && index == -1; i++)
	{
		if (this->m_componentList[i] == component)
			index = i;
	}

	if (index != -1)
		this->m_componentList.erase(this->m_componentList.begin() + index);
}

Component* GameObject::findComponentByName(std::string name)
{
	for (int i = 0; i < this->m_componentList.size(); i++)
	{
		if (this->m_componentList[i]->getName() == name)
		{
			return this->m_componentList[i];
		}
	}

	return nullptr;
}

Component* GameObject::findComponentOfType(Component::ComponentType type, std::string name)
{
	for (int i = 0; i < this->m_componentList.size(); i++)
	{
		if (this->m_componentList[i]->getName() == name && this->m_componentList[i]->getType() == type)
		{
			return this->m_componentList[i];
		}
	}

	return NULL;
}

GameObject::ComponentList GameObject::getComponentsOfType(Component::ComponentType type)
{
	std::vector<Component*> components;
	for (int i = 0; i < this->m_componentList.size(); i++)
	{
		if (this->m_componentList[i]->getType() == type)
		{
			components.push_back(this->m_componentList[i]);
		}
	}

	return components;
}

GameObject::ComponentList GameObject::getComponentsOfTypeRecursive(Component::ComponentType type)
{
	std::vector<Component*> components;
	for (int i = 0; i < this->m_componentList.size(); i++)
	{
		if (this->m_componentList[i]->getType() == type)
		{
			components.push_back(this->m_componentList[i]);
		}
	}

	return components;
}

void GameObject::onDestroy()
{
}
