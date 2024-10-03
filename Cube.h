#pragma once

#include "GameObject.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"

using namespace engine::graphics;

class Cube : public GameObject
{
private:
	vertex vertex_list[8];
	Vector3D color;

	VertexBuffer* m_vb;
	IndexBuffer* m_ib;
	VertexShader* m_vs;
	PixelShader* m_ps;

public:
	Cube(Vector3D position, Vector3D scale, Vector3D color);
	~Cube();

public:
	void onCreate() override;
	void update(float deltaTime) override;
	void draw(ConstantBuffer* cb) override;
	void onDestroy() override;

	void setPosition(Vector3D position) override;
	void setScale(Vector3D scale) override;
	void setColor(Vector3D color);
};

