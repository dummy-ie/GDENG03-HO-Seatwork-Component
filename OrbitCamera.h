#pragma once

#include "Camera.h"

class OrbitCamera : public Camera
{
private:
	GameObject* objectToOrbit;

	float speed = 0.0f;
	float angle = 0.0f;

public:
	OrbitCamera(std::string name);
	~OrbitCamera();

public:
	void update(float deltaTime) override;
	void setObjectToOrbit(GameObject* objectToOrbit);
	void setSpeed(float speed);
};
