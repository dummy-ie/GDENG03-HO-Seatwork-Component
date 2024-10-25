#pragma once

#include "UIScreen.h"

class CreditsScreen : public UIScreen
{
private:
	float count = 0;

private:
	CreditsScreen();
	~CreditsScreen();

private:
	friend class UIManager;

private:
	virtual void draw() override;
};

