#include "GraphicsEngine.h"

#include <exception>

#include "RenderSystem.h"
#include "Logger.h"

using namespace graphics;

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return this->renderSystem;
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
		throw std::exception("Graphics Engine not created successfully");
	}
	debug::Logger::log(this, "Initialized");
}
GraphicsEngine::~GraphicsEngine()
{
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
