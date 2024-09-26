#pragma once

#include <d3d11.h>

namespace engine
{
	namespace graphics
	{
		class DeviceContext;

		class SwapChain
		{
		private:
			IDXGISwapChain* m_swap_chain;
			ID3D11RenderTargetView* m_rtv;

		private:
			friend class DeviceContext;

		public:
			SwapChain();
			~SwapChain();

		public:
			bool init(HWND hwnd, UINT width, UINT height);
			bool present(bool vsync);
			bool release();
		};
	}
}


