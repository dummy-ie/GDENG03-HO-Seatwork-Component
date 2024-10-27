#include "RasterizerState.h"

#include <exception>

#include "RenderSystem.h"
#include "Logger.h"

using namespace graphics;

RasterizerState::RasterizerState(RenderSystem* system, D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode) : system(system)
{
	D3D11_RASTERIZER_DESC desc = {};
	ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
	desc.FillMode = fillMode;
	desc.CullMode = cullMode;

	if (!debug::Logger::log(this, this->system->m_d3d_device->CreateRasterizerState(&desc, &m_rasterizer_state)))
		throw std::exception("RasterizerState not created successfully");
}

RasterizerState::~RasterizerState()
{
	m_rasterizer_state->Release();
}

void RasterizerState::updateState()
{
	//GraphicsEngine::getInstance()->getImmediateDeviceContext()->setRasterizerState(this);
}

void RasterizerState::setFillMode(D3D11_FILL_MODE fillMode)
{
	/*D3D11_RASTERIZER_DESC desc = {};
	ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
	m_rasterizer_state->GetDesc(&desc);
	desc.FillMode = fillMode;
	GraphicsEngine::getInstance()->m_d3d_device->CreateRasterizerState(&desc, &m_rasterizer_state);
	updateState();*/
}
