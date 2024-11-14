#pragma once

#include "GameObject.h"

class Plane : public GameObject
{
private:
	VertexBuffer* vertexBuffer;
	ConstantBuffer* constantBuffer;

	float deltaPosition;
	float deltaScale;
	float angle;

public:
	Plane(std::string name);
	~Plane();

public:
	void onCreate() override;
	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void onDestroy() override;

protected:
	struct vertex
	{
		Vector3D position;
		Vector3D color;
		Vector3D color2;
	};
};

