#pragma once

#include <vector>

#include "GameObject.h"

using namespace graphics;

class Circle : public GameObject
{
private:
	float radius;
	float sides;

	std::vector<vertex> list;
	Vector3D color;

	VertexBuffer* vertexBuffer;
	ConstantBuffer* constantBuffer;

	float speed;
	Vector3D direction;

public:
	Circle(std::string name, float radius, int sides, void* shaderByteCode, size_t sizeShader);
	~Circle();

public:
	void onCreate() override;
	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void onDestroy() override;
};

