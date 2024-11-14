#pragma once

#include "GameObject.h"

using namespace graphics;

class Quad : public GameObject
{
private:
	VertexBuffer* vertexBuffer;
	ConstantBuffer* constantBuffer;

	float deltaPosition;
	float deltaScale;
	float angle;

public:
	Quad(std::string name);
	~Quad();

public:
	void onCreate() override;
	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void onDestroy() override;
};

