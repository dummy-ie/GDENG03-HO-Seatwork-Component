#pragma once

#include "GameObject.h"

class Teapot : public GameObject
{
private:
	Mesh* teapotMesh;
	ConstantBuffer* constantBuffer;

public:
	Teapot(std::string name);
	~Teapot();

public:
	void onCreate() override;
	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void onDestroy() override;
};

