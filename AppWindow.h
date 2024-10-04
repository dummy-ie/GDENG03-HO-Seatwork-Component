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
#include "InputListener.h"

namespace application
{
	using namespace engine;
	using namespace graphics;
	class AppWindow : public Window, public InputListener
	{
	private:
		SwapChain* m_swap_chain;

		ConstantBuffer* m_cb;

		std::vector<Viewport*> viewPorts;
		std::vector<GameObject*> objectList;

		float m_angle = 0;
		float m_delta_pos;
		float m_delta_scale;

		float m_rot_x = 0.0f;
		float m_rot_y = 0.0f;

	public:
		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;

		virtual void onKeyDown(int key);
		virtual void onKeyUp(int key);

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


