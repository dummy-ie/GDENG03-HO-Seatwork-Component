#pragma once

#include <d3d11.h>

namespace graphics
{
    class RenderTexture
    {
    private:
        ID3D11Texture2D* renderTarget = nullptr;
        ID3D11RenderTargetView* renderTargetView = nullptr;
        ID3D11ShaderResourceView* shaderResourceView = nullptr;
        ID3D11DepthStencilView* depthStencilView = nullptr;

        size_t width;
        size_t height;

    private:
        friend class DeviceContext;
        friend class SwapChain;

    public:
        RenderTexture();
        ~RenderTexture();

        void resizeResources(size_t width, size_t height);

        ID3D11Texture2D* getRenderTarget();
        ID3D11RenderTargetView* getRenderTargetView();
        ID3D11ShaderResourceView* getShaderResourceView();
    };
}