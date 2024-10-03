#pragma once

#include <d3d11.h>

#include "Rasterizer.h"

namespace engine
{
	namespace graphics
	{
		class Viewport
		{
		private:
			D3D11_VIEWPORT vp;
			Rasterizer rasterizer;

		private:
			friend class DeviceContext;

		public:
			Viewport();
			~Viewport();

		public:
			void setPosition(FLOAT topLeftX, FLOAT topLeftY);
			void setSize(FLOAT width, FLOAT height);
			void setDepth(FLOAT minDepth, FLOAT maxDepth);

			void init(FLOAT topLeftX, FLOAT topLeftY, FLOAT width, FLOAT height, FLOAT minDepth,
				FLOAT maxDepth, D3D11_FILL_MODE fillMode = D3D11_FILL_SOLID);
			void release();
		};
	}
}
