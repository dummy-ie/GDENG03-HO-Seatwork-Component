#pragma once

#include <d3d11.h>
#include <Windows.h>

namespace engine
{
	namespace graphics
	{
		class DeviceContext;

		class IndexBuffer
		{
		private:
			UINT m_size_list;

			ID3D11Buffer* m_buffer;

		private:
			friend class DeviceContext;

		public:
			IndexBuffer();
			~IndexBuffer();

		public:
			bool load(void* list_indices, UINT size_list);

			UINT getSizeIndexList();
			bool release();
		};
	}
}