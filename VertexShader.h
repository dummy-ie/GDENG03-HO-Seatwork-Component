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
			ID3D11VertexShader* vertexShader;

		private:
			friend class GraphicsEngine;
			friend class DeviceContext;

		public:
			VertexShader();
			~VertexShader();

		private:
			bool init(const void* shaderByteCode, size_t byteCodeSize);

		public:
			void release();
		};
	}
}
