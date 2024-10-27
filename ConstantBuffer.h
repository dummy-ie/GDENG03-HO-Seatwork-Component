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
		ConstantBuffer(RenderSystem* system);
		~ConstantBuffer();

	public:
		bool load(void* buffer, UINT size_buffer);
		void update(DeviceContext* context, void* buffer);
		bool release();
	};
}
