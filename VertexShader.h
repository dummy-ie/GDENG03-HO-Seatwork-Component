#pragma once

#include <d3d11.h>
#include "Prerequisites.h"

namespace graphics
{
	class VertexShader
	{
	private:
		RenderSystem* system = nullptr;
		ID3D11VertexShader* vertexShader;

	private:
		friend class RenderSystem;
		friend class DeviceContext;

	public:
		VertexShader(RenderSystem* system, const void* shaderByteCode, size_t byteCodeSize);
		~VertexShader();
	};
}
