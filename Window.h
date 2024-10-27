#pragma once

#include <Windows.h>

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
	virtual void onFocus();
	virtual void onKillFocus();

	bool init();
	bool broadcast();
	bool release();
	bool isRunning();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);
};