#include "RenderSystem.h"

#include <exception>
#include <d3dcompiler.h>

#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "RasterizerState.h"
#include "Viewport.h"

#include "Logger.h"

using namespace graphics;

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

bool RenderSystem::init()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT result = 0;
	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		result = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);

		if (SUCCEEDED(result))
			break;

		++driver_type_index;
	}

	if (!debug::Logger::log(this, result))
		return false;

	m_imm_device_context = new DeviceContext(this, m_imm_context);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	debug::Logger::log(this, "Initialized");

	return true;
}

bool RenderSystem::release()
{
	if (m_vs)
		m_vs->Release();
	if (m_ps)
		m_ps->Release();

	if (m_vsblob)
		m_vsblob->Release();
	if (m_psblob)
		m_psblob->Release();

	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	delete m_imm_device_context;

	m_d3d_device->Release();

	debug::Logger::log(this, "Released");
	delete this;
	return true;
}

SwapChain* RenderSystem::createSwapChain(HWND hwnd, UINT width, UINT height)
{
	SwapChain* swapChain = nullptr;
	try
	{
		swapChain = new SwapChain(this, hwnd, width, height);
	}
	catch(...) {}
	return swapChain;
}

VertexBuffer* RenderSystem::createVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader)
{
	VertexBuffer* vertexBuffer = nullptr;
	try
	{
		vertexBuffer = new VertexBuffer(this, list_vertices, size_vertex, size_list, shader_byte_code, size_byte_shader);
	}
	catch (...) {}
	return vertexBuffer;
}

IndexBuffer* RenderSystem::createIndexBuffer(void* list_indices, UINT size_list)
{
	IndexBuffer* indexBuffer = nullptr;
	try
	{
		indexBuffer = new IndexBuffer(this, list_indices, size_list);
	}
	catch (...) {}
	return indexBuffer;
}

ConstantBuffer* RenderSystem::createConstantBuffer(void* buffer, UINT size_buffer)
{
	ConstantBuffer* constantBuffer = nullptr;
	try
	{
		constantBuffer = new ConstantBuffer(this, buffer, size_buffer);
	}
	catch (...) {}
	return constantBuffer;
}

VertexShader* RenderSystem::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	VertexShader* vertexShader = nullptr;
	try
	{
		vertexShader = new VertexShader(this, shader_byte_code, byte_code_size);
	}
	catch (...) {}
	return vertexShader;
}

PixelShader* RenderSystem::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShader* pixelShader = nullptr;
	try
	{
		pixelShader = new PixelShader(this, shader_byte_code, byte_code_size);
	}
	catch (...) {}
	return pixelShader;
}

Viewport* RenderSystem::createViewport(FLOAT topLeftX, FLOAT topLeftY, FLOAT width, FLOAT height, FLOAT minDepth,
	FLOAT maxDepth)
{
	Viewport* viewport = nullptr;
	try
	{
		viewport = new Viewport(this, topLeftX, topLeftY, width, height, minDepth, maxDepth);
	}
	catch (...) {}
	return viewport;
}

RasterizerState* RenderSystem::createRasterizerState(D3D11_FILL_MODE fillMode, D3D11_CULL_MODE cullMode)
{
	RasterizerState* rasterizerState = nullptr;
	try
	{
		rasterizerState = new RasterizerState(this, fillMode, cullMode);
	}
	catch (...) {}
	return rasterizerState;
}

DeviceContext* RenderSystem::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

IDXGIFactory* RenderSystem::getDirectXFactory()
{
	return this->m_dxgi_factory;
}

ID3D11Device* RenderSystem::getDirectXDevice()
{
	return this->m_d3d_device;
}

bool RenderSystem::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob)
			error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

bool RenderSystem::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code,
	size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob)
			error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

void RenderSystem::releaseCompiledShader()
{
	if (m_blob)
		m_blob->Release();
}
