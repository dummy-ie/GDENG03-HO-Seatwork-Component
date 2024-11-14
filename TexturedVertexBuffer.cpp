#include "TexturedVertexBuffer.h"

#include <exception>

#include "RenderSystem.h"
#include "Logger.h"

using namespace graphics;

TexturedVertexBuffer::TexturedVertexBuffer(RenderSystem* system) : VertexBuffer(system) {}

TexturedVertexBuffer::~TexturedVertexBuffer()
{
	VertexBuffer::~VertexBuffer();
}

void TexturedVertexBuffer::load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code,
	UINT size_byte_shader)
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {  };
	init_data.pSysMem = list_vertices;

	m_size_vertex = size_vertex;
	m_size_list = size_list;

	if (!debug::Logger::log(this, this->system->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
		throw std::exception("TexturedVertexBuffer not created successfully");

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		// SEMANTINC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGHNED BYT OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}

	};

	UINT size_layout = ARRAYSIZE(layout);

	if (!debug::Logger::log(this, this->system->m_d3d_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_layout)))
		throw std::exception("InputLayout not created successfully");
}
