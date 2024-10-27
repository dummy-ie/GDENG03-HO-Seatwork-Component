#include "Texture.h"
#include <DirectXTex.h>

#include "Logger.h"
#include "GraphicsEngine.h"

using namespace graphics;

Texture::Texture(const wchar_t* fullPath) : Resource(fullPath)
{
	DirectX::ScratchImage imageData;
	HRESULT result = DirectX::LoadFromWICFile(fullPath, DirectX::WIC_FLAGS_NONE, nullptr, imageData);

	if (debug::Logger::log(this, result))
	{
		ID3D11Device* device = GraphicsEngine::getInstance()->getRenderSystem()->getDirectXDevice();
		
		result = DirectX::CreateTexture(device, imageData.GetImages(), imageData.GetImageCount(), imageData.GetMetadata(), &texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = imageData.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = (UINT)imageData.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		device->CreateShaderResourceView(this->texture, &desc, &shaderResourceView);
	}
	else
	{
		throw std::exception("Texture not created successfully");
	}
}

Texture::~Texture()
{
	shaderResourceView->Release();
	texture->Release();
}
