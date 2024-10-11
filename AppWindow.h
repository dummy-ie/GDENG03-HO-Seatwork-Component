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
		SwapChain* swapChain;

		std::vector<Viewport*> viewPorts;
		
		VertexShader* vertexShader;
		PixelShader* pixelShader;
	public:
		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;

		virtual void onKeyDown(int key) override;
		virtual void onKeyUp(int key) override;

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


