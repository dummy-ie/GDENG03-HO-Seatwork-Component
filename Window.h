#pragma once

#include <Windows.h>

namespace engine
{
	class Window
	{
	protected:
		HWND m_hwnd;
		bool m_is_running;
	public:
		Window();
		~Window();

	public:
		virtual void onCreate();
		virtual void onUpdate();
		virtual void onDestroy();

		bool init();
		bool broadcast();
		bool release();
		bool isRunning();

		RECT getClientWindowRect();
		void setHWND(HWND hwnd);
	};
}