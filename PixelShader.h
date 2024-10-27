#pragma once

#include <d3d11.h>
#include "Prerequisites.h"

namespace graphics
{
	class PixelShader
	{
	private:
		RenderSystem* system = nullptr;
		ID3D11PixelShader* m_ps;

	private:
		friend class RenderSystem;
		friend class DeviceContext;

	public:
		PixelShader(RenderSystem* system, const void* shader_byte_code, size_t byte_code_size);
		~PixelShader();
	};
}


