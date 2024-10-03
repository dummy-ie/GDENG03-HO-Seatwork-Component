#pragma once

#include <vector>

#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "GameObject.h"

namespace application
{
	using namespace engine;
	using namespace graphics;
	class AppWindow : public Window
	{
	private:
		SwapChain* m_swap_chain;

		ConstantBuffer* m_cb;

		std::vector<Viewport*> viewPorts;
		std::vector<GameObject*> objectList;

		float m_angle = 0;
		float m_delta_pos;
		float m_delta_scale;
	public:
		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;

		void initializeEngine();
		void updateQuadPosition();

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


