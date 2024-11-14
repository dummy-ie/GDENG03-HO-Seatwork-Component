#pragma once

#include "GameObject.h"

class Border : public GameObject
{
private:
	VertexBuffer* vertexBuffer;
	ConstantBuffer* constantBuffer;

public:
	Border(std::string name);
	~Border();

public:
	void onCreate() override;
	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void onDestroy() override;
};

