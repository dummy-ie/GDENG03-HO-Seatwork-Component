#pragma once

#include "Prerequisites.h"

namespace graphics
{
	class GraphicsEngine
	{
	private:
		RenderSystem* renderSystem = nullptr;

	public:
		// Initialize the Graphics Engine and DirectX 11 Device
		bool init();
		// Release all the resources loaded
		bool release();

	public:
		RenderSystem* getRenderSystem();

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
