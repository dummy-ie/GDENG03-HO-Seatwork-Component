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
	std::vector<unsigned int> indices;
	Vector3D color;

	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	ConstantBuffer* m_cb;
	VertexShader* m_vs;
	PixelShader* m_ps;

	float m_speed;
	Vector3D m_direction;
	Vector3D direction;

public:
	Circle(float radius, int sides, Vector3D position, Vector3D scale, Vector3D color);
	~Circle();

public:
	void onCreate() override;
	void update(float deltaTime) override;
	void draw() override;
	void onDestroy() override;

	void setPosition(Vector3D position) override;
	void setScale(Vector3D scale) override;
	void setColor(Vector3D color);
};

