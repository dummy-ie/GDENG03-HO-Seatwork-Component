#pragma once

#include <vector>
#include <Windows.h>

#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "GameObject.h"
#include "Quad.h"
#include "EngineTime.h"

namespace application
{
	using namespace engine;
	using namespace graphics;
	class AppWindow : public Window
	{
	private:
		SwapChain* m_swap_chain;

		std::vector<Viewport*> viewPorts;
		std::vector<GameObject*> objectList;

	public:
		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;

		void initializeEngine();

	private:
		static AppWindow* P_SHARED_INSTANCE;

	private:
		AppWindow();
		~AppWindow();
		AppWindow(AppWindow const&);
		AppWindow& operator = (AppWindow const&);

	public:
		static AppWindow* getInstance();
		static void initialize();
		static void destroy();
	};
}


