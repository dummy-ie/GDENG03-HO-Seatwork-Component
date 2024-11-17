#include "PhysicsComponent.h"

#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"
#include "GameObject.h"
#include "Vector3D.h"

using namespace GDEngine;

PhysicsComponent::PhysicsComponent(std::string name, GameObject* owner) : Component(name, Physics, owner)
{
	BaseComponentSystem::getInstance()->getPhysicsSystem()->registerComponent(this);
	PhysicsCommon* physicsCommon = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
	PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();

	const Vector3D scale = this->getOwner()->getLocalScale();
	const Vector3D position = this->getOwner()->getLocalPosition();
	const Vector3D rotation = this->getOwner()->getLocalRotation();

	Quaternion quaternion = Quaternion::fromEulerAngles(rotation.x, rotation.y, rotation.z);
	//Transform transform = Transform(Vector3(position.x, position.y, position.z), quaternion);

	Transform transform;
	transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());

	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.x / 1.9, scale.y / 1.9, scale.z / 1.9));

	this->m_rigidBody = physicsWorld->createRigidBody(transform);
	this->m_rigidBody->addCollider(boxShape, transform);
	this->m_rigidBody->updateMassPropertiesFromColliders();
	this->m_rigidBody->setMass(this->m_mass);
	this->m_rigidBody->setType(BodyType::DYNAMIC);

	transform = this->m_rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->setLocalMatrix(matrix);
	//const Vector3 position1 = transform.getPosition();
	//const Quaternion orientation = transform.getOrientation();
	//const Vector3 rotation1 = orientation.getVectorV();

	//this->getOwner()->setPosition(Vector3D(position1.x, position1.y, position1.z));
	//this->getOwner()->setRotation(Vector3D(rotation1.x, rotation1.y, rotation1.z));
}

PhysicsComponent::~PhysicsComponent()
{
	BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);
	Component::~Component();

	PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();
	physicsWorld->destroyRigidBody(this->m_rigidBody);
}

void PhysicsComponent::perform(float deltaTime)
{
	/*const Transform transform = this->m_rigidBody->getTransform();
	const Vector3 position = transform.getPosition();
	const Quaternion orientation = transform.getOrientation();
	const Vector3 rotation = orientation.getVectorV();
	
	this->getOwner()->setPosition(Vector3D(position.x, position.y, position.z));
	//this->getOwner()->setRotation(Vector3D(rotation.x, rotation.y, rotation.z));*/
	Transform transform = this->m_rigidBody->getTransform();
	const Vector3 position = transform.getPosition();
	const Quaternion orientation = transform.getOrientation();

	//this->getOwner()->setPosition(Vector3D(position.x, position.y, position.z));
	//this->getOwner()->setOrientation(Vector4D(orientation.x, orientation.y, orientation.z, orientation.w));
	
	//this->m_rigidBody->setTransform(Transform(position, orientation));
	//transform = Transform(position, quaternion);
	//this->m_rigidBody->setTransform(transform);
	float matrix[16];
	transform.getOpenGLMatrix(matrix);
	//this->getOwner()->setLocalMatrix(Vector4D(orientation.x, orientation.y, orientation.z, orientation.w), matrix);
	this->getOwner()->setLocalMatrix(matrix);
	const Vector3D position2 = this->getOwner()->getLocalPosition();

	//this->getOwner()->setLocalMatrix(Vector3D(position.x, position.y, position.z), Vector4D(orientation.x, orientation.y, orientation.z, orientation.w), matrix);
	Logger::log("Updating Component : " + this->m_name);
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return this->m_rigidBody;
}
