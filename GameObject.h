#pragma once

#include <string>

#include "VertexShader.h"
#include "Matrix4x4.h"
#include "Vector3D.h"

namespace engine
{
	class Window;
	namespace graphics
	{
		class VertexShader;
		class PixelShader;
	}
}

using namespace math;
using namespace engine;
using namespace engine::graphics;

class GameObject
{
protected:
	std::string name;	
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;
	bool active;

public:
	GameObject(std::string name);
	~GameObject();

public:
	virtual void update(float deltaTime) = 0;
	virtual void draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader) = 0;

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

	std::string getName();

	bool isActive();
	void setActive(bool active);

	struct vertex
	{
		Vector3D position;
		Vector3D color;
		Vector3D color2;
	};

	__declspec(align(16))
	struct CBData
	{
		Matrix4x4 worldMatrix;
		Matrix4x4 viewMatrix;
		Matrix4x4 projMatrix;
		float time;
	};
public:
	virtual void onCreate();
	virtual void onDestroy();
};

