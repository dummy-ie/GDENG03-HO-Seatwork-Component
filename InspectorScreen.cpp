#include "InspectorScreen.h"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "UIManager.h"
#include "GameObjectManager.h"

InspectorScreen::InspectorScreen() : UIScreen("InspectorScreen")
{
}

InspectorScreen::~InspectorScreen()
{
}

void InspectorScreen::draw()
{
	ImGui::SetNextWindowSize(ImVec2(UIManager::WINDOW_WIDTH / 6, UIManager::WINDOW_HEIGHT), ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2(UIManager::WINDOW_WIDTH * 5 / 6 - 20, 20), ImGuiCond_Once);
	ImGui::Begin("Inspector", &isActive);
	
	this->updateInspector();

	ImGui::End();
}

void InspectorScreen::updateInspector()
{
	GameObject* gameObject = GameObjectManager::getInstance()->getSelectedObject();
	if (gameObject != NULL)
	{
		std::string name = gameObject->getName();
		bool isActive = gameObject->isActive();
		if (ImGui::InputText("Name", &name))
		{
			gameObject->setName(name);
		}
		if (ImGui::Checkbox("Active", &isActive))
		{
			gameObject->setActive(isActive);
		}
		Vector3D objectPosition = gameObject->getLocalPosition();
		float position[3] = { objectPosition.x, objectPosition.y, objectPosition.z};
		if (ImGui::DragFloat3("Position", position, 0.01f))
		{
			gameObject->setPosition(Vector3D(position[0], position[1], position[2]));
		}
		Vector3D objectScale = gameObject->getLocalScale();
		float scale[3] = { objectScale.x, objectScale.y, objectScale.z };
		if (ImGui::DragFloat3("Scale", scale, 0.01f))
		{
			gameObject->setScale(Vector3D(scale[0], scale[1], scale[2]));
		}
		Vector3D objectRotation = gameObject->getLocalRotation();
		float rotation[3] = { objectRotation.x, objectRotation.y, objectRotation.z };
		if (ImGui::DragFloat3("Rotation", rotation, 0.01f))
		{
			gameObject->setRotation(Vector3D(rotation[0], rotation[1], rotation[2]));
		}
		if (ImGui::Button("Delete", ImVec2(ImGui::GetWindowSize().x - 15, 20)))
		{
			GameObjectManager::getInstance()->setSelectedObject(nullptr);
			GameObjectManager::getInstance()->deleteObject(gameObject);
		}
	}
}