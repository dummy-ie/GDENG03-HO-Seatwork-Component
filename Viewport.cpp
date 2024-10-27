#include "Viewport.h"

#include "RenderSystem.h"
#include "DeviceContext.h"
#include "Logger.h"
#include "RasterizerState.h"

using namespace graphics;

Viewport::Viewport(RenderSystem* system) : system(system)
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
	this->system->getImmediateDeviceContext()->setRasterizerState(solidState);
}

void Viewport::setRasterizerWireframeState()
{
	this->system->getImmediateDeviceContext()->setRasterizerState(wireframeState);
}

void Viewport::init(FLOAT topLeftX, FLOAT topLeftY, FLOAT width, FLOAT height, FLOAT minDepth, FLOAT maxDepth)
{
	solidState = this->system->createRasterizerState();
	wireframeState = this->system->createRasterizerState(D3D11_FILL_WIREFRAME, D3D11_CULL_NONE);

	setPosition(topLeftX, topLeftY);
	setSize(width, height);
	setDepth(minDepth, maxDepth);

	setRasterizerSolidState();
	debug::Logger::log(this,"Initialized");
}

void Viewport::release()
{
	solidState->release();
	wireframeState->release();
	delete this;
}
