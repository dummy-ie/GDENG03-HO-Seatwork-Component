#include "RenderTexture.h"

#include <algorithm>

#include "GraphicsEngine.h"
#include "Logger.h"

using namespace graphics;

RenderTexture::RenderTexture() : width(0), height(0)
{
    this->renderTarget = NULL;
    resizeResources(width, height);
}

RenderTexture::~RenderTexture()
{
    renderTargetView->Release();
    depthStencilView->Release();
    shaderResourceView->Release();
    renderTarget->Release();
}

void RenderTexture::resizeResources(size_t width, size_t height)
{
    ID3D11Device* device = GraphicsEngine::getInstance()->getRenderSystem()->getDirectXDevice();
    if (width == this->width && height == this->height || width == 0 || height == 0)
        return;

    if (this->width > UINT32_MAX || this->height > UINT32_MAX)
    {
        throw std::out_of_range("Invalid width/height");
    }

    if (!device)
        return;

    CD3D11_TEXTURE2D_DESC renderTargetDesc = {};
    renderTargetDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    renderTargetDesc.Width = static_cast<UINT>(width);
    renderTargetDesc.Height = static_cast<UINT>(height);
    renderTargetDesc.ArraySize = 1; // The render target view has only one texture.
    renderTargetDesc.MipLevels = 1; // Use a single mipmap level.
    renderTargetDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    renderTargetDesc.Usage = D3D11_USAGE_DEFAULT;
    renderTargetDesc.CPUAccessFlags = 0;
    renderTargetDesc.SampleDesc.Count = 1;
    
    if (!debug::Logger::log(this, device->CreateTexture2D(&renderTargetDesc, nullptr, &this->renderTarget)))
        throw std::exception("Texture not created successfully");

    if (!debug::Logger::log(this, device->CreateRenderTargetView(renderTarget, NULL, &this->renderTargetView)))
        throw std::exception("Render Target View not created successfully");

    if (!debug::Logger::log(this, device->CreateShaderResourceView(renderTarget, NULL, &this->shaderResourceView)))
        throw std::exception("Shader Resource View not created successfully");

    D3D11_TEXTURE2D_DESC texDesc = {};
    texDesc.Width = width;
    texDesc.Height = height;
    texDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    texDesc.Usage = D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    texDesc.MipLevels = 1;
    texDesc.SampleDesc.Count = 1;
    texDesc.SampleDesc.Quality = 0;
    texDesc.MiscFlags = 0;
    texDesc.ArraySize = 1;
    texDesc.CPUAccessFlags = 0;

    ID3D11Texture2D* buffer = NULL;

    if (!debug::Logger::log(this, device->CreateTexture2D(&texDesc, NULL, &buffer)))
        throw std::exception("Texture2D not created successfully");

    if (!debug::Logger::log(this, device->CreateDepthStencilView(buffer, NULL, &depthStencilView)))
        throw std::exception("Depth Stencil View not created successfully");

    this->width = width;
    this->height = height;
}

ID3D11Texture2D* RenderTexture::getRenderTarget()
{
    return this->renderTarget;
}

ID3D11RenderTargetView* RenderTexture::getRenderTargetView()
{
    return this->renderTargetView;
}

ID3D11ShaderResourceView* RenderTexture::getShaderResourceView()
{
    return this->shaderResourceView;
}
