#pragma once

#include "GameObject.h"

#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"

using namespace engine::graphics;

__declspec(align(16))
struct constant
{
	float m_angle;
};

class Quad : public GameObject
{
private:
	vertex list[4];
	vec3 color;

	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;
	ConstantBuffer* m_cb;

	float m_angle = 0;

public:
	Quad(vec3 position, vec3 scale, vec3 color);
	~Quad();

public:
	void onCreate() override;
	void update(float deltaTime) override;
	void draw() override;
	void onDestroy() override;
	void setPosition(vec3 position) override;
	void setScale(vec3 scale) override;
	void setColor(vec3 color);
};

