#include "ToolsScreen.h"

#include "imgui.h"
#include "UIManager.h"
#include "GraphicsEngine.h"
#include "GameObjectManager.h"
#include "CameraManager.h"

ToolsScreen::ToolsScreen() : UIScreen("ToolsScreen")
{
    debug::Logger::log(this, "Initialized");
}

ToolsScreen::~ToolsScreen()
{
}

void ToolsScreen::draw()
{
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Scene Camera")) {
            if (ImGui::MenuItem("Orthographic")) {
                CameraManager::getInstance()->setSceneCameraProjection(0);
            }
            if (ImGui::MenuItem("Perspective")) {
                CameraManager::getInstance()->setSceneCameraProjection(1);
            }
            if (ImGui::MenuItem("Top Down")) {
                CameraManager::getInstance()->setSceneCameraProjection(2);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
