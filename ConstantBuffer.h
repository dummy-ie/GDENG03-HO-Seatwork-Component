#pragma once

#include <d3d11.h>
#include "Prerequisites.h"

namespace graphics
{
	class ConstantBuffer
	{
	private:
		RenderSystem* system = nullptr;
		ID3D11Buffer* m_buffer;

	private:
		friend class DeviceContext;

	public:
		ConstantBuffer(RenderSystem* system, void* buffer, UINT size_buffer);
		~ConstantBuffer();

	public:
		void update(DeviceContext* context, void* buffer);
	};
}
