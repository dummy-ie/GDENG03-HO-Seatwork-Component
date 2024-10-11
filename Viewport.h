#pragma once

#include <d3d11.h>

#include "RasterizerState.h"

namespace engine
{
	namespace graphics
	{
		class Viewport
		{
		private:
			D3D11_VIEWPORT vp;
			RasterizerState* solidState;
			RasterizerState* wireframeState;

		private:
			friend class DeviceContext;

		public:
			Viewport();
			~Viewport();

		public:
			void setPosition(FLOAT topLeftX, FLOAT topLeftY);
			void setSize(FLOAT width, FLOAT height);
			void setDepth(FLOAT minDepth, FLOAT maxDepth);
			void setRasterizerSolidState();
			void setRasterizerWireframeState();

			void init(FLOAT topLeftX, FLOAT topLeftY, FLOAT width, FLOAT height, FLOAT minDepth,
				FLOAT maxDepth);
			void release();
		};
	}
}
