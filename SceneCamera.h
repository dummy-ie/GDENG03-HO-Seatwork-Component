#pragma once

#include "Camera.h"

class SceneCamera : public Camera, InputListener
{
private:
	float speed = 1.0f;

	bool isRightMouseDown = false;

public:
	SceneCamera(std::string name);
	~SceneCamera();

public:
	void update(float deltaTime) override;
	void setSpeed(float speed);

	virtual void onKeyDown(int key);
	virtual void onKeyUp(int key);

	virtual void onMouseMove(const Vector2D& deltaMousePosition);

	virtual void onLeftMouseDown(const Vector2D& mousePosition);
	virtual void onLeftMouseUp(const Vector2D& mousePosition);

	virtual void onRightMouseDown(const Vector2D& mousePosition);
	virtual void onRightMouseUp(const Vector2D& mousePosition);
};

