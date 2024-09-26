#pragma once

#include "GameObject.h"

#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

using namespace engine::graphics;

class Quad : public GameObject
{
private:
	vertex list[4];


	VertexBuffer* m_vb;
	VertexShader* m_vs;
	PixelShader* m_ps;

public:
	Quad(vec3 position, vec3 scale, vec3 color);
	~Quad();

public:
	void onCreate() override;
	void update() override;
	void draw() override;
	void onDestroy() override;
	void setPosition(vec3 position) override;
	void setScale(vec3 scale) override;
	void setColor(vec3 color) override;
};

