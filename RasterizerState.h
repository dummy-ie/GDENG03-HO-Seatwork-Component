#pragma once

#include <d3d11.h>
#include "Prerequisites.h"

namespace graphics
{
	class RasterizerState
	{
	private:
		RenderSystem* system = nullptr;
		ID3D11RasterizerState* m_rasterizer_state;
		// desc;

	private:
		friend class Viewport;
		friend class DeviceContext;

	public:
		RasterizerState(RenderSystem* system, D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode);
		~RasterizerState();
	};
}