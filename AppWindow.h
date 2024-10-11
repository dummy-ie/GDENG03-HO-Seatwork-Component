#pragma once

#include <vector>
#include <stack>

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

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_angle;
};


namespace application
{
	using namespace engine;
	using namespace graphics;
	class AppWindow : public Window, public InputListener
	{
	private:
		SwapChain* m_swap_chain;

		std::vector<Viewport*> viewPorts;
		std::vector<GameObject*> objectList;
		std::stack<GameObject*> objectStack;
		//std::stack<GameObject*> objectList;
		ConstantBuffer* m_cb;
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


