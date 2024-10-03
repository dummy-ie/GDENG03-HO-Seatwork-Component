#pragma once

#include <d3d11.h>

namespace engine
{
	namespace graphics
	{
		class Rasterizer
		{
		private:
			ID3D11RasterizerState* m_rasterizer_state;
			D3D11_RASTERIZER_DESC desc;

		private:
			friend class Viewport;
			friend class DeviceContext;

		public:
			Rasterizer();
			~Rasterizer();

		private:
			void updateState();
		public:
			bool init();
			bool release();

			void setFillMode(D3D11_FILL_MODE fillMode);
		};
	}
}