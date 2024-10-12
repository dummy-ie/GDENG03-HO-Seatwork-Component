#pragma once

#include "GameObject.h"
#include "InputListener.h"

namespace engine
{
	namespace graphics
	{
		class VertexBuffer;
		class ConstantBuffer;
	}
}

class Plane : public GameObject
{
private:
	VertexBuffer* vertexBuffer;
	ConstantBuffer* constantBuffer;

	float deltaPosition;
	float deltaScale;
	float angle;

public:
	Plane(std::string name, void* shaderByteCode, size_t sizeShader);
	~Plane();

public:
	void onCreate() override;
	void update(float deltaTime) override;
	void draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void onDestroy() override;
};

