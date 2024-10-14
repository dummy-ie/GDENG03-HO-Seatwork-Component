#pragma once

#include "Camera.h"

class FirstPersonCamera : public Camera
{
private:
	float speed = 1.0f;
	float forward = 0.0f;
	float right = 0.0f;

public:
	FirstPersonCamera(std::string name);
	~FirstPersonCamera();

public:
	void update(float deltaTime) override;
	void setSpeed(float speed);
};

