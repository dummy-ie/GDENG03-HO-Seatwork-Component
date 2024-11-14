#include "GraphicsEngine.h"

#include <exception>

#include "RenderSystem.h"
#include "Logger.h"
#include "ShaderLibrary.h"

using namespace graphics;

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return this->renderSystem;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return this->textureManager;
}

MeshManager* GraphicsEngine::getMeshManager()
{
	return this->meshManager;
}

GraphicsEngine* GraphicsEngine::P_SHARED_INSTANCE = NULL;
GraphicsEngine::GraphicsEngine()
{
	try
	{
		this->renderSystem = new RenderSystem();
	}
	catch (...)
	{
		throw std::exception("RenderSystem not created successfully");
	}
	try
	{
		this->textureManager = new TextureManager();
	}
	catch (...)
	{
		throw std::exception("TextureManager not created successfully");
	}
	try
	{
		this->meshManager = new MeshManager();
	}
	catch (...)
	{
		throw std::exception("MeshManager not created successfully");
	}
	debug::Logger::log(this, "Initialized");
}
GraphicsEngine::~GraphicsEngine()
{
	delete meshManager;
	delete textureManager;
	delete renderSystem;
	P_SHARED_INSTANCE = nullptr;
	debug::Logger::log(this, "Released");
}
GraphicsEngine::GraphicsEngine(const GraphicsEngine&) {}

GraphicsEngine* GraphicsEngine::getInstance() {
	return P_SHARED_INSTANCE;
}

void GraphicsEngine::initialize()
{
	if (P_SHARED_INSTANCE)
		throw std::exception("Graphics Engine already created");
	P_SHARED_INSTANCE = new GraphicsEngine();
}

void GraphicsEngine::destroy()
{
	if (P_SHARED_INSTANCE)
	{
		delete P_SHARED_INSTANCE;
	}
}
