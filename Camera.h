#pragma once

#include "GameObject.h"
#include "InputListener.h"

class Camera : public GameObject
{
public:
	Camera(std::string name);
	~Camera();

public:
	void onCreate() override;
	virtual void update(float deltaTime) override;
	void onDestroy() override;
};

