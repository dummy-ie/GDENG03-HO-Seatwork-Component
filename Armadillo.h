#pragma once

#include "GameObject.h"

class Armadillo : public GameObject
{
private:
	Mesh* mesh;
	ConstantBuffer* constantBuffer;

public:
	Armadillo(std::string name);
	~Armadillo();

public:
	void onCreate() override;
	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void onDestroy() override;
};

