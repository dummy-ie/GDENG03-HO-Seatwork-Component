#include "VertexShader.h"

#include <exception>

#include "RenderSystem.h"
#include "Logger.h"

using namespace graphics;

VertexShader::VertexShader(RenderSystem* system, const void* shaderByteCode, size_t byteCodeSize) : system(system)
{
	if (!debug::Logger::log(this, this->system->m_d3d_device->CreateVertexShader(shaderByteCode, byteCodeSize, nullptr, &vertexShader)))
		throw std::exception("VertexShader not created successfully");
}

VertexShader::~VertexShader()
{
	vertexShader->Release();
}