#pragma once

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
	vec3 color;

public:
	GameObject(vec3 position, vec3 scale, vec3 color);
	~GameObject();

public:
	virtual void update(float deltaTime);
	virtual void draw();
	virtual void setPosition(vec3 position);
	virtual void setScale(vec3 scale);
	virtual void setColor(vec3 color);
public:
	virtual void onCreate();
	virtual void onDestroy();
};

