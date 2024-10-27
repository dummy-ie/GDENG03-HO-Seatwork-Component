#pragma once

#include <d3d11.h>
#include "Prerequisites.h"

namespace graphics
{
	class RenderSystem
	{
	private:
		DeviceContext* m_imm_device_context;

	private:
		ID3D11Device* m_d3d_device;
		D3D_FEATURE_LEVEL m_feature_level;

	private:
		IDXGIDevice* m_dxgi_device;
		IDXGIAdapter* m_dxgi_adapter;
		IDXGIFactory* m_dxgi_factory;
		ID3D11DeviceContext* m_imm_context;

	private:
		ID3DBlob* m_blob = nullptr;

		ID3DBlob* m_vsblob = nullptr;
		ID3DBlob* m_psblob = nullptr;
		ID3D11VertexShader* m_vs = nullptr;
		ID3D11PixelShader* m_ps = nullptr;

	private:
		friend class SwapChain;
		friend class VertexBuffer;
		friend class IndexBuffer;
		friend class ConstantBuffer;
		friend class VertexShader;
		friend class PixelShader;
		friend class Viewport;
		friend class RasterizerState;

	public:
		RenderSystem();
		~RenderSystem();

	public:
		SwapChain* createSwapChain(HWND hwnd, UINT width, UINT height);
		VertexBuffer* createVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
		IndexBuffer* createIndexBuffer(void* list_indices, UINT size_list);
		ConstantBuffer* createConstantBuffer(void* buffer, UINT size_buffer);
		VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
		PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);
		Viewport* createViewport(FLOAT topLeftX, FLOAT topLeftY, FLOAT width, FLOAT height, FLOAT minDepth, FLOAT maxDepth);
		RasterizerState* createRasterizerState(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode);

		DeviceContext* getImmediateDeviceContext();
		IDXGIFactory* getDirectXFactory();
		ID3D11Device* getDirectXDevice();

	public:
		bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
		bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
		void releaseCompiledShader();
	};
}
