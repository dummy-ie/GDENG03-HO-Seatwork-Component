#pragma once

#include <d3d11.h>
#include "Prerequisites.h"

namespace graphics
{
	class SwapChain
	{
	private:
		RenderSystem* system = nullptr;

		IDXGISwapChain* m_swap_chain;
		ID3D11RenderTargetView* m_rtv;
		ID3D11DepthStencilView* m_dsv;

	private:
		friend class DeviceContext;

	public:
		SwapChain(RenderSystem* system);
		~SwapChain();

	public:
		bool init(HWND hwnd, UINT width, UINT height);
		bool present(bool vsync);
		bool release();
	};
}