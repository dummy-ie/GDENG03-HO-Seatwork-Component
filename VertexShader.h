#pragma once

#include <d3d11.h>

namespace engine
{
	namespace graphics
	{
		class GraphicsEngine;
		class DeviceContext;
		class VertexShader
		{
		private:
			ID3D11VertexShader* m_vs;

		private:
			friend class GraphicsEngine;
			friend class DeviceContext;

		public:
			VertexShader();
			~VertexShader();

		private:
			bool init(const void* shader_byte_code, size_t byte_code_size);

		public:
			void release();
		};
	}
}
