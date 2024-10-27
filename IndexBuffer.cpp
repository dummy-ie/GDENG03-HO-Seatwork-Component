#include "IndexBuffer.h"

#include "RenderSystem.h"
#include "Logger.h"

using namespace graphics;

IndexBuffer::IndexBuffer(RenderSystem* system) : system(system), m_buffer(0)
{
}

IndexBuffer::~IndexBuffer()
{
}

bool IndexBuffer::load(void* list_indices, UINT size_list)
{
	if (m_buffer)
		m_buffer->Release();

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = 4 * size_list;
	buff_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {  };
	init_data.pSysMem = list_indices;

	m_size_list = size_list;

	if (!debug::Logger::log(this, this->system->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
		return false;

	return true;
}

UINT IndexBuffer::getSizeIndexList()
{
	return this->m_size_list;
}

bool IndexBuffer::release()
{
	m_buffer->Release();
	delete this;
	return true;
}
