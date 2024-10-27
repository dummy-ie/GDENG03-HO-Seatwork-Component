#pragma once

#include "GameObject.h"

class Border : public GameObject
{
private:
	VertexBuffer* vertexBuffer;
	ConstantBuffer* constantBuffer;

public:
	Border(std::string name, void* shaderByteCode, size_t sizeShader);
	~Border();

public:
	void onCreate() override;
	void update(float deltaTime) override;
	void draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void onDestroy() override;
};

