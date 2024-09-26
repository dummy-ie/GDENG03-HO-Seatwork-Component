#pragma once

#include <d3d11.h>
#include <Windows.h>

namespace engine
{
	namespace graphics
	{
		class DeviceContext;

		class ConstantBuffer
		{
		private:
			ID3D11Buffer* m_buffer;

		private:
			friend class DeviceContext;

		public:
			ConstantBuffer();
			~ConstantBuffer();

		public:
			bool load(void* buffer, UINT size_buffer);
			void update(DeviceContext* context, void* buffer);
			bool release();
		};
	}
}


