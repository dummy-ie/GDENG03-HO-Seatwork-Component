#pragma once

#define NOMINMAX

#include <Windows.h>
#include "UIManager.h"
class Window
{
protected:
	HWND m_hwnd;
	bool m_is_running;
	bool isInitialized = false;

public:
	Window();
	~Window();

public:
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	virtual void onFocus();
	virtual void onKillFocus();

	bool broadcast();
	bool isRunning();

	RECT getClientWindowRect();
};