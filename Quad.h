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
	Quad(std::string name, void* shaderByteCode, size_t sizeShader);
	~Quad();

public:
	void onCreate() override;
	void update(float deltaTime) override;
	void draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void onDestroy() override;
};

