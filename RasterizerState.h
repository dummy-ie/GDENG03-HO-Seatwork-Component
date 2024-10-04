#pragma once

#include <d3d11.h>

namespace engine
{
	namespace graphics
	{
		class RasterizerState
		{
		private:
			ID3D11RasterizerState* m_rasterizer_state;
			// desc;

		private:
			friend class Viewport;
			friend class DeviceContext;

		public:
			RasterizerState();
			~RasterizerState();

		private:
			void updateState();
		public:
			bool init(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode);
			bool release();

			void setFillMode(D3D11_FILL_MODE fillMode);
		};
	}
}