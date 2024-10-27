#include "Viewport.h"

#include <exception>

#include "RenderSystem.h"
#include "DeviceContext.h"
#include "Logger.h"
#include "RasterizerState.h"

using namespace graphics;

Viewport::Viewport(RenderSystem* system, FLOAT topLeftX, FLOAT topLeftY, FLOAT width, FLOAT height, FLOAT minDepth, FLOAT maxDepth) : system(system)
{
	vp = {};
	solidState = this->system->createRasterizerState(D3D11_FILL_SOLID, D3D11_CULL_BACK);
	wireframeState = this->system->createRasterizerState(D3D11_FILL_WIREFRAME, D3D11_CULL_NONE);

	setPosition(topLeftX, topLeftY);
	setSize(width, height);
	setDepth(minDepth, maxDepth);

	setRasterizerSolidState();
	debug::Logger::log(this, "Initialized");
}

Viewport::~Viewport()
{
	delete solidState;
	delete wireframeState;
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
	this->system->getImmediateDeviceContext()->setRasterizerState(solidState);
}

void Viewport::setRasterizerWireframeState()
{
	this->system->getImmediateDeviceContext()->setRasterizerState(wireframeState);
}