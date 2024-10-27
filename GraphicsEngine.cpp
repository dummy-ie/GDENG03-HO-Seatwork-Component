#include "GraphicsEngine.h"

#include "RenderSystem.h"
#include "Logger.h"

using namespace graphics;

bool GraphicsEngine::init()
{
	this->renderSystem = new RenderSystem();
	this->renderSystem->init();
	debug::Logger::log(this, "Initialized");
	return true;
}

bool GraphicsEngine::release()
{
	this->renderSystem->release();
	debug::Logger::log(this, "Released");
	delete this;
	return true;
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return this->renderSystem;
}

GraphicsEngine* GraphicsEngine::P_SHARED_INSTANCE = NULL;
GraphicsEngine::GraphicsEngine() {}
GraphicsEngine::~GraphicsEngine() {}
GraphicsEngine::GraphicsEngine(const GraphicsEngine&) {}

GraphicsEngine* GraphicsEngine::getInstance() {
	return P_SHARED_INSTANCE;
}

void GraphicsEngine::initialize()
{
	P_SHARED_INSTANCE = new GraphicsEngine();
	P_SHARED_INSTANCE->init();
}

void GraphicsEngine::destroy()
{
	if (P_SHARED_INSTANCE != NULL)
	{
		debug::Logger::log(P_SHARED_INSTANCE, "Released");
		P_SHARED_INSTANCE->release();
	}
}
