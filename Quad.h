#pragma once

#include "GameObject.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"

using namespace engine::graphics;

class Quad : public GameObject
{
private:
	vertex list[4];
	Vector3D color;

	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;

public:
	Quad(Vector3D position, Vector3D scale, Vector3D color);
	~Quad();

public:
	void onCreate() override;
	void update(float deltaTime) override;
	void draw(ConstantBuffer* cb) override;
	void onDestroy() override;

	void setPosition(Vector3D position) override;
	void setScale(Vector3D scale) override;
	void setColor(Vector3D color);
};

