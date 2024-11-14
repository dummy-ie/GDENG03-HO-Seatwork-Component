#include "ShaderLibrary.h"

#include "GraphicsEngine.h"
#include "Logger.h"
#include "VertexShader.h"
#include "PixelShader.h"

using namespace graphics;

void ShaderLibrary::requestVertexShaderData(std::wstring vertexShaderName, void** shaderByteCode, size_t* sizeShader)
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();
	renderSystem->compileVertexShader(vertexShaderName.c_str(), "main", shaderByteCode, sizeShader);
}

VertexShader* ShaderLibrary::getVertexShader(std::wstring vertexShaderName)
{
	if (this->activeVertexShaders[vertexShaderName] == NULL)
		debug::Logger::log(L"Vertex shader " + vertexShaderName + L" not found.");

	return this->activeVertexShaders[vertexShaderName];
}

PixelShader* ShaderLibrary::getPixelShader(std::wstring pixelShaderName)
{
	if (this->activePixelShaders[pixelShaderName] == NULL)
		debug::Logger::log(L"Pixel shader " + pixelShaderName + L" not found.");

	return this->activePixelShaders[pixelShaderName];
}

ShaderLibrary::ShaderLibrary()
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	ShaderNames shaderNames;
	ShaderData shaderData;

	renderSystem->compileVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME.c_str(), "main", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.BASE_VERTEX_SHADER_NAME] = renderSystem->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);

	renderSystem->compilePixelShader(shaderNames.BASE_PIXEL_SHADER_NAME.c_str(), "main", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activePixelShaders[shaderNames.BASE_PIXEL_SHADER_NAME] = renderSystem->createPixelShader(shaderData.shaderByteCode, shaderData.sizeShader);

	renderSystem->compileVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME.c_str(), "main", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.TEXTURED_VERTEX_SHADER_NAME] = renderSystem->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);

	renderSystem->compilePixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME.c_str(), "main", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activePixelShaders[shaderNames.TEXTURED_PIXEL_SHADER_NAME] = renderSystem->createPixelShader(shaderData.shaderByteCode, shaderData.sizeShader);

	renderSystem->compileVertexShader(shaderNames.VERTEX_MESH_LAYOUT_SHADER_NAME.c_str(), "main", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.VERTEX_MESH_LAYOUT_SHADER_NAME] = renderSystem->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);

	debug::Logger::log(this, "Initialized");
}

ShaderLibrary::~ShaderLibrary()
{
	ShaderNames shaderNames;
	delete this->activeVertexShaders[shaderNames.BASE_VERTEX_SHADER_NAME];
	delete this->activePixelShaders[shaderNames.BASE_PIXEL_SHADER_NAME];

	this->activeVertexShaders.clear();
	this->activePixelShaders.clear();
	debug::Logger::log(this, "Destroyed");
}

ShaderLibrary* ShaderLibrary::P_SHARED_INSTANCE = NULL;
ShaderLibrary::ShaderLibrary(ShaderLibrary const&) {}
ShaderLibrary* ShaderLibrary::getInstance()
{
	return P_SHARED_INSTANCE;
}
void ShaderLibrary::initialize()
{
	if (P_SHARED_INSTANCE)
		throw std::exception("Shader Library already created");
	P_SHARED_INSTANCE = new ShaderLibrary();
}
void ShaderLibrary::destroy()
{
	if (P_SHARED_INSTANCE)
	{
		delete P_SHARED_INSTANCE;
	}
}