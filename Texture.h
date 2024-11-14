#pragma once

#include "Resource.h"
#include "DeviceContext.h"
#include <d3d11.h>

class Texture : public Resource
{
private:
	ID3D11Resource* texture = nullptr;
	ID3D11ShaderResourceView* shaderResourceView = nullptr;

	friend class CreditsScreen;
	friend class graphics::DeviceContext;
public:
	Texture(const wchar_t* fullPath);
	~Texture() override;
};

