#include "VertexShader.h"
#include "GraphicsEngine.h"

using namespace engine::graphics;

VertexShader::VertexShader()
{
}

VertexShader::~VertexShader()
{
}

bool VertexShader::init(const void* shaderByteCode, size_t byteCodeSize)
{
	if (!SUCCEEDED(GraphicsEngine::getInstance()->m_d3d_device->CreateVertexShader(shaderByteCode, byteCodeSize, nullptr, &vertexShader)))
		return false;
	return true;
}

void VertexShader::release()
{
	vertexShader->Release();
	delete this;
}
