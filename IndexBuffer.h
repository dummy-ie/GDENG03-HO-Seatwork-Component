#pragma once

#include <d3d11.h>
#include "Prerequisites.h"

namespace graphics
{
	class IndexBuffer
	{
	private:
		RenderSystem* system = nullptr;

		UINT m_size_list;
		ID3D11Buffer* m_buffer;

	private:
		friend class DeviceContext;

	public:
		IndexBuffer(RenderSystem* system);
		~IndexBuffer();

	public:
		bool load(void* list_indices, UINT size_list);

		UINT getSizeIndexList();
		bool release();
	};
}