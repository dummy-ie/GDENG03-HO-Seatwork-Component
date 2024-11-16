#include "GameObject.h"

#include "BaseComponentSystem.h"
#include "Logger.h"
#include "PhysicsSystem.h"

GameObject::GameObject(std::string name)
{
	HRESULT result = CoCreateGuid(&guid);
	if (!debug::Logger::log(this, result))
		throw std::exception("Game Object GUID creation failed");

	this->name = name;
	this->localPosition = Vector3D::zero();
	this->localRotation = Vector3D::zero();
	this->localScale = Vector3D::one();
	this->orientation = Vector4D(0, 0, 0, 1);
	this->physics = false;

	this->updateLocalMatrix();

	this->active = true;
}

GameObject::~GameObject()
{
	for (Component* component : listComponents)
	{
		component->detachOwner();
	}
	this->listComponents.clear();
}

void GameObject::onCreate()
{
}

void GameObject::update(float deltaTime)
{
	debug::Logger::log("Updating Game Object : " + this->name);
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

void GameObject::setOrientation(Vector4D orientation)
{
	this->orientation = orientation;
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

void GameObject::updateLocalMatrix()
{
	if (!physics)
	{
		Matrix4x4 transform, rotation, translate;
		Matrix4x4 temp;

		// Scale
		transform.setIdentity();
		transform.setScale(this->localScale);

		// Scale * Rotation
		/*rotation.setIdentity();
		rotation.setRotationZ(this->localRotation.z);

		temp.setIdentity();
		temp.setRotationY(this->localRotation.y);
		rotation *= temp;

		temp.setIdentity();
		temp.setRotationX(this->localRotation.x);
		rotation *= temp;*/

		rotation.setIdentity();
		rotation.setRotation(this->orientation);

		// Scale * Rotation * Translation
		translate.setIdentity();
		translate.setTranslation(this->localPosition);


		translate *= rotation;
		transform *= translate;

		this->localMatrix = transform;
	}
}

void GameObject::setLocalMatrix(float matrix[16])
{
	Matrix4x4 transform, scale, translate, temp;

	/*transform.setIdentity();
	transform.setScale(this->localScale);

	temp.setIdentity();
	temp.setMatrix(matrix);

	transform *= temp;
	this->localMatrix = transform;*/

	//temp.setIdentity();
	//temp.setTranslation(this->localPosition);
	//transform *= temp;

	scale.setIdentity();
	scale.setScale(this->localScale);

	translate.setIdentity();
	translate.setTranslation(this->localPosition);

	temp.setIdentity();
	temp.setMatrix(matrix);
	//temp.getMatrix();
	//debug::Logger::log(temp.getTranslation().toString());

	translate *= temp;
	//translate.getMatrix();
	scale *= translate;
	transform = scale;

	this->localMatrix = transform;

	/*this->localPosition = Vector3D(matrix[12], matrix[13], matrix[14]);

	debug::Logger::log("[" + std::to_string(matrix[0]) + "," + std::to_string(matrix[1]) + "," + std::to_string(matrix[2]) + "," + std::to_string(matrix[3]) + "]");
	debug::Logger::log("[" + std::to_string(matrix[4]) + "," + std::to_string(matrix[5]) + "," + std::to_string(matrix[6]) + "," + std::to_string(matrix[7]) + "]");
	debug::Logger::log("[" + std::to_string(matrix[8]) + "," + std::to_string(matrix[9]) + "," + std::to_string(matrix[10]) + "," + std::to_string(matrix[11]) + "]");
	debug::Logger::log("[" + std::to_string(matrix[12]) + "," + std::to_string(matrix[13]) + "," + std::to_string(matrix[14]) + "," + std::to_string(matrix[15]) + "]");

	//matrix[12] = 0;
	//matrix[13] = 0;
	//matrix[14] = 0;

	scale.setIdentity();
	scale.setScale(this->localScale);

	/*temp.setIdentity();
	temp.setMatrix(matrix);

	temp.getMatrix();

	Matrix4x4 rotate;
	rotate.setIdentity();
	rotate.setRotation(orientation);
	rotate.transpose();
	rotate.getMatrix();

	translate.setIdentity();
	translate.setTranslation(this->localPosition);

	/*debug::Logger::log("[" + std::to_string(m_mat[0]) + "," + std::to_string(m_mat[1]) + "," + std::to_string(m_mat[2]) + "," + std::to_string(m_mat[3]) + "]");
	debug::Logger::log("[" + std::to_string(m_mat[4]) + "," + std::to_string(m_mat[5]) + "," + std::to_string(m_mat[6]) + "," + std::to_string(m_mat[7]) + "]");
	debug::Logger::log("[" + std::to_string(m_mat[8]) + "," + std::to_string(m_mat[9]) + "," + std::to_string(m_mat[10]) + "," + std::to_string(m_mat[11]) + "]");
	debug::Logger::log("[" + std::to_string(m_mat[12]) + "," + std::to_string(m_mat[13]) + "," + std::to_string(m_mat[14]) + "," + std::to_string(m_mat[15]) + "]");

	translate *= rotate;
	translate.getMatrix();
	scale *= translate;
	transform = scale;

	this->localMatrix = transform;*/
	//this->localPosition = this->localMatrix.getTranslation();
}

void GameObject::setLocalMatrix(Vector3D position, Vector4D orientation, float matrix[16])
{
	Matrix4x4 transform, scale, translate, temp;

	this->localPosition = position;
	this->orientation = orientation;

	scale.setIdentity();
	scale.setScale(this->localScale);

	temp.setIdentity();
	temp.setMatrix(matrix);

	//translate *= temp;
	scale *= temp;
	transform = scale;

	this->localMatrix = transform;
}

float* GameObject::getLocalMatrix()
{
	return this->localMatrix.getMatrix();
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
	rotation.setRotationZ(this->localRotation.z);

	temp.setIdentity();
	temp.setRotationY(this->localRotation.y);
	rotation *= temp;

	temp.setIdentity();
	temp.setRotationX(this->localRotation.x);
	rotation *= temp;

	transform *= rotation;
	// Scale * Rotation * Translation
	temp.setIdentity();
	temp.setTranslation(this->localPosition);
	transform *= temp;

	return transform.getMatrix();
}

bool GameObject::isActive()
{
	return this->active;

}

void GameObject::setActive(bool active)
{
	this->active = active;
}

bool GameObject::isPhysics()
{
	return this->physics;
}

void GameObject::setPhysics(bool physics)
{
	this->physics = physics;
}

void GameObject::attachComponent(Component* component)
{
	this->listComponents.push_back(component);
	component->attachOwner(this);
}

void GameObject::detachComponent(Component* component)
{
	int index = -1;

	for (int i = 0; i < this->listComponents.size() && index == -1; i++)
	{
		if (this->listComponents[i] == component)
			index = i;
	}

	if (index != -1)
		this->listComponents.erase(this->listComponents.begin() + index);
}

Component* GameObject::findComponentByName(std::string name)
{
	for (int i = 0; i < this->listComponents.size(); i++)
	{
		if (this->listComponents[i]->getName() == name)
		{
			return this->listComponents[i];
		}
	}

	return NULL;
}

Component* GameObject::findComponentOfType(Component::ComponentType type, std::string name)
{
	for (int i = 0; i < this->listComponents.size(); i++)
	{
		if (this->listComponents[i]->getName() == name && this->listComponents[i]->getType() == type)
		{
			return this->listComponents[i];
		}
	}

	return NULL;
}

std::vector<Component*> GameObject::getComponentsOfType(Component::ComponentType type)
{
	std::vector<Component*> components;
	for (int i = 0; i < this->listComponents.size(); i++)
	{
		if (this->listComponents[i]->getType() == type)
		{
			components.push_back(this->listComponents[i]);
		}
	}

	return components;
}

std::vector<Component*> GameObject::getComponentsOfTypeRecursive(Component::ComponentType type)
{
	std::vector<Component*> components;
	for (int i = 0; i < this->listComponents.size(); i++)
	{
		if (this->listComponents[i]->getType() == type)
		{
			components.push_back(this->listComponents[i]);
		}
	}

	return components;
}

void GameObject::onDestroy()
{
}
