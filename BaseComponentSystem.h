#pragma once


class PhysicsSystem;
class BaseComponentSystem
{
private:
	PhysicsSystem* physicsSystem;

public:
	PhysicsSystem* getPhysicsSystem();

private:
	static BaseComponentSystem* P_SHARED_INSTANCE;

private:
	BaseComponentSystem();
	~BaseComponentSystem();
	BaseComponentSystem(BaseComponentSystem const&);
	BaseComponentSystem& operator = (BaseComponentSystem const&);

public:
	static BaseComponentSystem* getInstance();
	static void initialize();
	static void destroy();
};

