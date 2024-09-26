#pragma once

#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include <vector>
#include "GameObject.h"
#include "Quad.h"
#include <Windows.h>

namespace application
{
	using namespace engine;
	using namespace graphics;
	class AppWindow : public Window
	{
	private:
		SwapChain* m_swap_chain;
		VertexBuffer* m_vb;
		VertexBuffer* m_vb2;
		VertexBuffer* m_vb3;
		VertexShader* m_vs;
		PixelShader* m_ps;
		ConstantBuffer* m_cb;

		std::vector<GameObject*> objectList;

		unsigned long m_old_time = 0;
		float m_delta_time = 0;
		float m_angle = 0;

	public:
		AppWindow();
		~AppWindow();

	public:
		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;
	};
}


