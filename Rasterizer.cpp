#include "Rasterizer.h"

#include "GraphicsEngine.h"

using namespace engine::graphics;

Rasterizer::Rasterizer()
{
}

Rasterizer::~Rasterizer()
{
}

void Rasterizer::updateState()
{
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setRasterizerState(this);
}

bool Rasterizer::init()
{
	ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK;

	if (!SUCCEEDED(GraphicsEngine::getInstance()->m_d3d_device->CreateRasterizerState(&desc, &m_rasterizer_state)))
		return false;

	updateState();
	return true;
}

bool Rasterizer::release()
{
	m_rasterizer_state->Release();
	//delete this;
	return true;
}

void Rasterizer::setFillMode(D3D11_FILL_MODE fillMode)
{
	desc.FillMode = fillMode;
	GraphicsEngine::getInstance()->m_d3d_device->CreateRasterizerState(&desc, &m_rasterizer_state);
	updateState();
}
