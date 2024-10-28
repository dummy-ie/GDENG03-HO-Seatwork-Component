#pragma comment(lib, "rpcrt4.lib")

#include "HierarchyScreen.h"

#include "imgui.h"
#include "UIManager.h"
#include "GameObjectManager.h"

HierarchyScreen::HierarchyScreen() : UIScreen("HierarchyScreen")
{
	debug::Logger::log(this, "Initialized");
}

HierarchyScreen::~HierarchyScreen()
{
}

void HierarchyScreen::draw()
{
	ImGui::SetNextWindowSize(ImVec2(UIManager::WINDOW_WIDTH / 6, UIManager::WINDOW_HEIGHT), ImGuiCond_Once);
	ImGui::Begin("Hierarchy", &isActive);
	
	std::vector<GameObject*> list = GameObjectManager::getInstance()->getAllObjects();

	for (GameObject* gameObject : list)
	{
		std::string guidString;
		GUID guid = gameObject->getGuid();
		RPC_CSTR rpcString = NULL;

		UuidToStringA(&guid, &rpcString);
		guidString = (char*)rpcString;
		std::string label = gameObject->getName() + "###" + guidString;
		::RpcStringFreeA(&rpcString);

		if (ImGui::Button(label.c_str(), ImVec2(ImGui::GetWindowSize().x - 15, 20)))
		{
			debug::Logger::log("Selected : " + label);
			GameObjectManager::getInstance()->setSelectedObject(gameObject);
		}
	}

	ImGui::End();
}
