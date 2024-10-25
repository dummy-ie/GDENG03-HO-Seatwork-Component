#include "HierarchyScreen.h"

#include "imgui.h"
#include "UIManager.h"
#include "GameObjectManager.h"

HierarchyScreen::HierarchyScreen() : UIScreen("HierarchyScreen")
{
}

HierarchyScreen::~HierarchyScreen()
{
}

void HierarchyScreen::draw()
{
	ImGui::SetNextWindowSize(ImVec2(UIManager::WINDOW_WIDTH / 6, UIManager::WINDOW_HEIGHT), ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2(UIManager::WINDOW_WIDTH * 4 / 6 - 20, 20), ImGuiCond_Once);
	ImGui::Begin("Hierarchy", &isActive);
	
	std::vector<GameObject*> list = GameObjectManager::getInstance()->getAllObjects();

	for (GameObject* gameObject : list)
	{
		if (ImGui::Button(gameObject->getName().c_str(), ImVec2(ImGui::GetWindowSize().x - 15, 20)))
		{
			GameObjectManager::getInstance()->setSelectedObject(gameObject);
		}
	}

	ImGui::End();
}
