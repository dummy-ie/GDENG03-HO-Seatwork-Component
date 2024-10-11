#pragma once

#include <vector>
#include <cmath>

#include "GameObject.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"

using namespace engine::graphics;

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
	void draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void onDestroy() override;
};

