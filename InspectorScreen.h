#pragma once
#include "GameObject.h"
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
	void drawInspector(GameObject* gameObject);
	void drawTransformTable(GameObject* gameObject);
};