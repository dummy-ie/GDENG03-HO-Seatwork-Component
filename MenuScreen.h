#pragma once

#include "UIScreen.h"

namespace GDEditor
{
	class MenuScreen : public UIScreen
	{
	private:
		MenuScreen();
		~MenuScreen();

	private:
		friend class UIManager;

	private:
		virtual void draw() override;
	};
}

