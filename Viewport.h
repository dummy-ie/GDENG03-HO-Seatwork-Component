#pragma once

#include <d3d11.h>
#include "Prerequisites.h"

namespace graphics
{
	class Viewport
	{
	private:
		RenderSystem* system = nullptr;
		D3D11_VIEWPORT vp;

	private:
		friend class DeviceContext;

	public:
		Viewport(RenderSystem* system, FLOAT topLeftX, FLOAT topLeftY, FLOAT width, FLOAT height, FLOAT minDepth,
			FLOAT maxDepth);
		~Viewport();

	public:
		void setPosition(FLOAT topLeftX, FLOAT topLeftY);
		void setSize(FLOAT width, FLOAT height);
		void setDepth(FLOAT minDepth, FLOAT maxDepth);
		
	};
}