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
		ConstantBuffer* constantBuffer;
	public:
		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;
		virtual void onFocus() override;
		virtual void onKillFocus() override;

		virtual void onKeyDown(int key) override;
		virtual void onKeyUp(int key) override;
		virtual void onMouseMove(const Vector2D& deltaMousePosition) override;

		virtual void onLeftMouseDown(const Vector2D& mousePosition) override;
		virtual void onLeftMouseUp(const Vector2D& mousePosition) override;

		virtual void onRightMouseDown(const Vector2D& mousePosition) override;
		virtual void onRightMouseUp(const Vector2D& mousePosition) override;

		void initializeEngine();

	private:
		void update();

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


