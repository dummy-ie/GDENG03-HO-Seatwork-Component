#include "Viewport.h"

#include "GraphicsEngine.h"

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

void Viewport::setRasterizerSolidState()
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setRasterizerState(solidState);
}

void Viewport::setRasterizerWireframeState()
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setRasterizerState(wireframeState);
}

void Viewport::init(FLOAT topLeftX, FLOAT topLeftY, FLOAT width, FLOAT height, FLOAT minDepth, FLOAT maxDepth)
{
	solidState = GraphicsEngine::getInstance()->createRasterizerState();
	wireframeState = GraphicsEngine::getInstance()->createRasterizerState(D3D11_FILL_WIREFRAME, D3D11_CULL_NONE);

	setPosition(topLeftX, topLeftY);
	setSize(width, height);
	setDepth(minDepth, maxDepth);

	setRasterizerSolidState();
}

void Viewport::release()
{
	solidState->release();
	wireframeState->release();
	delete this;
}
