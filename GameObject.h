#pragma once

#include "ConstantBuffer.h"
#include "Matrix4x4.h"
#include "Vector3D.h"

using namespace math;
using namespace engine::graphics;

struct vertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

class GameObject
{
protected:
	Vector3D position;
	Vector3D scale;

public:
	GameObject(Vector3D position, Vector3D scale);
	~GameObject();

public:
	virtual void update(float deltaTime);
	virtual void draw(ConstantBuffer* cb);
	virtual void setPosition(Vector3D position);
	virtual void setScale(Vector3D scale);

public:
	virtual void onCreate();
	virtual void onDestroy();
};

