#pragma once

#include "UIScreen.h"

class ProfilerScreen : public UIScreen
{
private:
	ProfilerScreen();
	~ProfilerScreen();

private:
	friend class UIManager;

private:
	virtual void draw() override;
};
