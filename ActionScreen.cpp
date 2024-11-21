#include "ActionScreen.h"

#include "ActionHistory.h"
#include "GameObjectManager.h"
#include "imgui.h"
#include "Logger.h"

namespace GDEditor
{
	using namespace GDEngine;
	ActionScreen::ActionScreen() : UIScreen("ActionScreen")
	{
		Logger::log(this, "Initialized");
	}

	ActionScreen::~ActionScreen()
	{
	}

	void ActionScreen::draw()
	{
		ImGui::Begin("Actions", &isActive);

		if (ImGui::Button("Undo"))
		{
			if (ActionHistory::getInstance()->hasRemainingUndoActions())
			{
				GameObjectManager::getInstance()->applyAction(ActionHistory::getInstance()->undoAction());
			}
			else Logger::log("Empty Undo");
		}
		if (ImGui::Button("Redo"))
		{
			if (ActionHistory::getInstance()->hasRemainingRedoActions())
			{
				GameObjectManager::getInstance()->applyAction(ActionHistory::getInstance()->redoAction());
			}
			else Logger::log("Empty Redo");
		}

		ImGui::End();
	}
}

