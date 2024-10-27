#pragma once

#include "Prerequisites.h"
#include "RenderSystem.h"
#include "TextureManager.h"

namespace graphics
{
	class GraphicsEngine
	{
	private:
		RenderSystem* renderSystem = nullptr;
		TextureManager* textureManager = nullptr;

	public:
		RenderSystem* getRenderSystem();
		TextureManager* getTextureManager();

	private:
		static GraphicsEngine* P_SHARED_INSTANCE;

	private:
		GraphicsEngine();
		~GraphicsEngine();
		GraphicsEngine(GraphicsEngine const&);
		GraphicsEngine& operator = (GraphicsEngine const&);

	public:
		static GraphicsEngine* getInstance();
		static void initialize();
		static void destroy();
	};
}
