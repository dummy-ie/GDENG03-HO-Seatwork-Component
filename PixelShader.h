#pragma once

#include <d3d11.h>

namespace engine
{
	namespace graphics
	{
		class GraphicsEngine;
		class DeviceContext;
		class PixelShader
		{
		private:
			ID3D11PixelShader* m_ps;

		private:
			friend class GraphicsEngine;
			friend class DeviceContext;

		public:
			PixelShader();
			~PixelShader();

		private:
			bool init(const void* shader_byte_code, size_t byte_code_size);

		public:
			void release();
		};
	}
}


