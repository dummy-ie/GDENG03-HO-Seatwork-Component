#include "VertexShader.h"

#include "RenderSystem.h"
#include "Logger.h"

using namespace graphics;

VertexShader::VertexShader(RenderSystem* system) : system(system)
{
}

VertexShader::~VertexShader()
{
}

bool VertexShader::init(const void* shaderByteCode, size_t byteCodeSize)
{
	if (!debug::Logger::log(this, this->system->m_d3d_device->CreateVertexShader(shaderByteCode, byteCodeSize, nullptr, &vertexShader)))
		return false;

	return true;
}

void VertexShader::release()
{
	vertexShader->Release();
	delete this;
}
