#pragma once
#include "UIScreen.h"

class InspectorScreen : public UIScreen
{

private:
	InspectorScreen();
	~InspectorScreen();

private:
	friend class UIManager;

private:
	virtual void draw() override;
	void updateInspector();
};