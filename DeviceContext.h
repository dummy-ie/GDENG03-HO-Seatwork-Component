#pragma once

#include <d3d11.h>
#include "Prerequisites.h"

namespace graphics
{
	class DeviceContext
	{
	private:
		RenderSystem* system = nullptr;
		ID3D11DeviceContext* m_device_context;

	private:
		friend class ConstantBuffer;

	public:
		DeviceContext(RenderSystem* system, ID3D11DeviceContext* device_context);
		~DeviceContext();

	public:
		ID3D11DeviceContext* getContext();

		void clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);
		void setVertexBuffer(VertexBuffer* vertex_buffer);
		void setIndexBuffer(IndexBuffer* index_buffer);

		void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
		void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
		void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
		void drawLineStrip(UINT vertex_count, UINT start_vertex_index);

		//void setViewportSize(UINT width, UINT height, int index);
		void setViewport(Viewport* vp);

		void setVertexShader(VertexShader* vertex_shader);
		void setPixelShader(PixelShader* pixel_shader);

		void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer, int index = 0);
		void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer, int index = 0);
		void setRasterizerState(RasterizerState* rasterizer_state);


		bool release();
	};
}

