#pragma once
#include "ConstantBuffer.h"

using namespace engine::graphics;

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

class GameObject
{
protected:
	vec3 position;
	vec3 scale;

public:
	GameObject(vec3 position, vec3 scale);
	~GameObject();

public:
	virtual void update();
	virtual void draw();
	virtual void setPosition(vec3 position);
	virtual void setScale(vec3 scale);

public:
	virtual void onCreate();
	virtual void onDestroy();
};

