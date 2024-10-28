#include "SwapChain.h"

#include <exception>

#include "RenderSystem.h"
#include "RenderTexture.h"
#include "Logger.h"

using namespace graphics;

SwapChain::SwapChain(RenderSystem* system, HWND hwnd, UINT width, UINT height) : system(system)
{
	ID3D11Device* device = this->system->m_d3d_device;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	// Create the swap chain for the window indicated by HWND parameter
	HRESULT hr = this->system->m_dxgi_factory->CreateSwapChain(device, &desc, &swapChain);

	if (!debug::Logger::log(this, hr))
		throw std::exception("SwapChain not created successfully");

	try
	{
		renderTexture = new RenderTexture();
	}
	catch(...) {}
}

SwapChain::~SwapChain()
{
	delete renderTexture;
	swapChain->Release();
}

void SwapChain::cleanRenderTarget()
{
	if (renderTexture->renderTargetView)
	{
		renderTexture->renderTargetView->Release();
		renderTexture->renderTargetView = nullptr;
	}
}

void SwapChain::resizeBuffers(UINT bufferCount, UINT width, UINT height)
{
	renderTexture->resizeResources(width, height);
	swapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
}

void SwapChain::createRenderTarget()
{
	ID3D11Texture2D* buffer = NULL;
	HRESULT result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (!debug::Logger::log(this, result))
		throw std::exception("Swap Chain Fail");

	result = this->system->m_d3d_device->CreateRenderTargetView(buffer, NULL, &renderTexture->renderTargetView);
	if (!debug::Logger::log(this, result))
		throw std::exception("Render Target View not created successfully.");

	buffer->Release();
}

bool SwapChain::present(bool vsync)
{
	swapChain->Present(vsync, NULL);
	return true;
}

RenderTexture* SwapChain::getRenderTexture()
{
	return this->renderTexture;
}
