#include "Viewport.h"

using namespace engine::graphics;

Viewport::Viewport()
{
	vp = {};
}

Viewport::~Viewport()
{
}

void Viewport::setPosition(FLOAT topLeftX, FLOAT topLeftY)
{
	vp.TopLeftX = topLeftX;
	vp.TopLeftY = topLeftY;
}

void Viewport::setSize(FLOAT width, FLOAT height)
{
	vp.Width = width;
	vp.Height = height;
}

void Viewport::setDepth(FLOAT minDepth, FLOAT maxDepth)
{
	vp.MinDepth = minDepth;
	vp.MaxDepth = maxDepth;
}

void Viewport::init(FLOAT topLeftX, FLOAT topLeftY, FLOAT width, FLOAT height, FLOAT minDepth, FLOAT maxDepth, D3D11_FILL_MODE fillMode)
{
	setPosition(topLeftX, topLeftY);
	setSize(width, height);
	setDepth(minDepth, maxDepth);
	rasterizer.init();
	rasterizer.setFillMode(fillMode);
}

void Viewport::release()
{
	rasterizer.release();
	delete this;
}
