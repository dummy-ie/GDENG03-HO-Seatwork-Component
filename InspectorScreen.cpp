#include "InspectorScreen.h"

#include "imgui.h"
#include "imgui_stdlib.h"
#include "UIManager.h"
#include "GameObjectManager.h"

InspectorScreen::InspectorScreen() : UIScreen("InspectorScreen")
{
	debug::Logger::log(this, "Initialized");
}

InspectorScreen::~InspectorScreen()
{
}

void InspectorScreen::draw()
{
	ImGui::SetNextWindowSize(ImVec2(UIManager::WINDOW_WIDTH / 6, UIManager::WINDOW_HEIGHT), ImGuiCond_Once);
	ImGui::Begin("Inspector", &isActive);
	
	this->drawInspector(GameObjectManager::getInstance()->getSelectedObject());

	ImGui::End();
}

void InspectorScreen::drawInspector(GameObject* gameObject)
{
	if (gameObject == NULL)
		return;

	std::string name = gameObject->getName();
	bool isActive = gameObject->isActive();

	if (ImGui::Checkbox("##Active", &isActive))
	{
		gameObject->setActive(isActive);
	}
	ImGui::SameLine();
	ImGui::SetNextItemWidth(-1);
	if (ImGui::InputText("##Name", &name))
	{
		if (ImGui::IsItemDeactivatedAfterEdit())
			gameObject->setName(name);
	}

	this->drawTransformTable(gameObject);
	
	if (ImGui::Button("Delete", ImVec2(ImGui::GetWindowSize().x - 15, 20)))
	{
		GameObjectManager::getInstance()->setSelectedObject(nullptr);
		GameObjectManager::getInstance()->deleteObject(gameObject);
	}
}

void InspectorScreen::drawTransformTable(GameObject* gameObject)
{
	int rows = 3;

	std::string labels[] = { "Position", "Rotation", "Scale"};

	Vector3D vectorValues[3];
	vectorValues[0] = gameObject->getLocalPosition();
	vectorValues[1] = gameObject->getLocalRotation();
	vectorValues[2] = gameObject->getLocalScale();

	if (ImGui::BeginTable("Transform", 2, ImGuiTableFlags_SizingFixedFit))
	{
		ImGui::TableSetupColumn("Label", ImGuiTableColumnFlags_WidthFixed);
		ImGui::TableSetupColumn("Values", ImGuiTableColumnFlags_WidthStretch);

		for (int i = 0; i < rows; i++)
		{
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text(labels[i].c_str());
			ImGui::TableNextColumn();
			ImGui::SetNextItemWidth(-1);
			float values[3] = { vectorValues[i].x, vectorValues[i].y, vectorValues[i].z };
			std::string dragLabel = "##" + labels[i];

			if (ImGui::DragFloat3(dragLabel.c_str(), values, 0.01f))
			{
				switch (i)
				{
				case 0:
					gameObject->setPosition(Vector3D(values[0], values[1], values[2]));
					break;
				case 1:
					gameObject->setRotation(Vector3D(values[0], values[1], values[2]));
					break;
				case 2:
					gameObject->setScale(Vector3D(values[0], values[1], values[2]));
					break;
				}
			}
		}

		ImGui::EndTable();
	}
}