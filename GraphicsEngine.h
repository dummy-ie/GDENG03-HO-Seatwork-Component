#pragma once

#include <d3d11.h>
#include "DeviceContext.h"

namespace engine
{
	namespace graphics
	{
		class SwapChain;
		//class DeviceContext;
		class VertexBuffer;
		class VertexShader;
		class ConstantBuffer;
		class PixelShader;

		class GraphicsEngine
		{
		private:
			DeviceContext* m_imm_device_context;

			ID3D11Device* m_d3d_device;
			D3D_FEATURE_LEVEL m_feature_level;

			IDXGIDevice* m_dxgi_device;
			IDXGIAdapter* m_dxgi_adapter;
			IDXGIFactory* m_dxgi_factory;
			ID3D11DeviceContext* m_imm_context;

			ID3DBlob* m_blob = nullptr;

			ID3DBlob* m_vsblob = nullptr;
			ID3DBlob* m_psblob = nullptr;
			ID3D11VertexShader* m_vs = nullptr;
			ID3D11PixelShader* m_ps = nullptr;
		private:
			friend class SwapChain;
			friend class VertexBuffer;
			friend class ConstantBuffer;
			friend class VertexShader;
			friend class PixelShader;

		public:
			SwapChain* createSwapChain();
			DeviceContext* getImmediateDeviceContext();
			VertexBuffer* createVertexBuffer();
			ConstantBuffer* createConstantBuffer();

			VertexShader* createVertexShader(const void* shader_byte_code, size_t byte_code_size);
			PixelShader* createPixelShader(const void* shader_byte_code, size_t byte_code_size);

			bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
			bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
			void releaseCompiledShader();

		private:
			// Initialize the Graphics Engine and DirectX 11 Device
			bool init();
			// Release all the resources loaded
			bool release();
		private:
			static GraphicsEngine* P_SHARED_INSTANCE;

		private:
			GraphicsEngine();
			~GraphicsEngine();
			GraphicsEngine(GraphicsEngine const&);
			GraphicsEngine& operator = (GraphicsEngine const&);

		public:
			static GraphicsEngine* getInstance();
			static void initialize();
			static void destroy();
		};
	}
}

