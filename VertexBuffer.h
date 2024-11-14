#pragma once

#include <d3d11.h>
#include "Prerequisites.h"

namespace graphics
{
	class VertexBuffer
	{
	protected:
		RenderSystem* system = nullptr;

		UINT m_size_vertex;
		UINT m_size_list;

		ID3D11InputLayout* m_layout;
		ID3D11Buffer* m_buffer;

	protected:
		friend class DeviceContext;

	public:
		VertexBuffer(RenderSystem* system);
		virtual ~VertexBuffer();

	public:
		virtual void load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);

	public:
		UINT getSizeVertexList();
	};
}