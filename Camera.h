#pragma once

#include "GameObject.h"
#include "InputListener.h"

class Camera : public GameObject, public InputListener
{
public:
	static Camera* main;

public:
	Camera(std::string name);
	~Camera();

public:
	void onCreate() override;
	void update(float deltaTime) override;
	void onDestroy() override;

	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Vector2D& deltaMousePosition) override;

	virtual void onLeftMouseDown(const Vector2D& mousePosition) override;
	virtual void onLeftMouseUp(const Vector2D& mousePosition) override;

	virtual void onRightMouseDown(const Vector2D& mousePosition) override;
	virtual void onRightMouseUp(const Vector2D& mousePosition) override;
};

