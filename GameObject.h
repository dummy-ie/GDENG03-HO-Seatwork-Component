#pragma once

#include <string>
#include <guiddef.h>

#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "VertexShader.h"

#include "Matrix4x4.h"
#include "Vector3D.h"

#include "EngineTime.h"
#include "InputSystem.h"

#include "Logger.h"

class Window;

using namespace math;
using namespace graphics;

class GameObject
{
protected:
	GUID guid;
	std::string name;

	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;

	friend class GameObjectManager;

private:
	bool active;

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
	Vector3D getLocalRotation();

	void setName(std::string name);
	std::string getName();
	GUID getGuid();

	bool isActive();
	void setActive(bool active);

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

