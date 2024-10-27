#include "PixelShader.h"

#include <exception>

#include "RenderSystem.h"
#include "Logger.h"

using namespace graphics;

PixelShader::PixelShader(RenderSystem* system, const void* shader_byte_code, size_t byte_code_size) : system(system)
{
	if (!debug::Logger::log(this, this->system->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps)))
		throw std::exception("PixelShader not created successfully");
}

PixelShader::~PixelShader()
{
	m_ps->Release();
}