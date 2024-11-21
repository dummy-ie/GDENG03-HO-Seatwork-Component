#pragma once

#include "UIScreen.h"

namespace GDEditor {
	class ActionScreen : public UIScreen
	{
	private:
		ActionScreen();
		~ActionScreen();

	private:
		friend class UIManager;

	private:
		virtual void draw() override;

	};
}

