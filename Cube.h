#pragma once

#include "GameObject.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "InputListener.h"

using namespace engine::graphics;

class Cube : public GameObject, public InputListener
{
private:
	//vertex vertex_list[8];
	//Vector3D color;

	VertexBuffer* vertexBuffer;
	ConstantBuffer* constantBuffer;
	IndexBuffer* indexBuffer;

	float deltaRotation;
	float angle;
	float speed = 1.0f;
	bool startRotate = false;

public:
	Cube(std::string name, void* shaderByteCode, size_t sizeShader);
	~Cube();

public:
	void onCreate() override;
	void update(float deltaTime) override;
	void draw(Window* window, VertexShader* vertexShader, PixelShader* pixelShader) override;
	void onDestroy() override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Vector2D& deltaMousePosition) override;

	virtual void onLeftMouseDown(const Vector2D& mousePosition) override;
	virtual void onLeftMouseUp(const Vector2D& mousePosition) override;

	virtual void onRightMouseDown(const Vector2D& mousePosition) override;
	virtual void onRightMouseUp(const Vector2D& mousePosition) override;

	void setSpeed(float speed);
};

