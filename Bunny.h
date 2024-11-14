#pragma once

#include "GameObject.h"

class Bunny : public GameObject
{
private:
	Mesh* mesh;
	ConstantBuffer* constantBuffer;

public:
	Bunny(std::string name);
	~Bunny();

public:
	void onCreate() override;
	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void onDestroy() override;
};

