#pragma once

#include "GameObject.h"

#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"

using namespace engine::graphics;

class OtherQuad : public GameObject
{
private:
	vertex list[4];
	vec3 color;

	ConstantBuffer* m_cb;
	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;

	float m_angle = 0;
	float m_delta_speed = 0;

public:
	OtherQuad(vec3 position, vec3 scale, vec3 color);
	~OtherQuad();

public:
	void onCreate() override;
	void update() override;
	void draw();
	void onDestroy() override;
	void setPosition(vec3 position) override;
	void setScale(vec3 scale) override;
	void setColor(vec3 color);
};