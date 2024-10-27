#include "PixelShader.h"

#include "RenderSystem.h"
#include "Logger.h"

using namespace graphics;

PixelShader::PixelShader(RenderSystem* system) : system(system)
{
}

PixelShader::~PixelShader()
{
}

bool PixelShader::init(const void* shader_byte_code, size_t byte_code_size)
{
	if (!debug::Logger::log(this, this->system->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps)))
		return false;
	return true;
}

void PixelShader::release()
{
	m_ps->Release();
	delete this;
}
