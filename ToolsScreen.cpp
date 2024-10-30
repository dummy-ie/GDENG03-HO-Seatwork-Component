#include "ToolsScreen.h"

#include "imgui.h"
#include "UIManager.h"
#include "GraphicsEngine.h"
#include "GameObjectManager.h"
#include "CameraManager.h"
#include "ViewportManager.h"

ToolsScreen::ToolsScreen() : UIScreen("ToolsScreen")
{
    debug::Logger::log(this, "Initialized");
}

ToolsScreen::~ToolsScreen()
{
}

void ToolsScreen::draw()
{
    if (ImGui::BeginMenu("Scene Camera")) {
        if (ImGui::MenuItem("Orthographic")) {
            CameraManager::getInstance()->setSceneCameraProjection(0);
        }
        if (ImGui::MenuItem("Perspective")) {
            CameraManager::getInstance()->setSceneCameraProjection(1);
        }
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Viewports")) {
        if (ImGui::MenuItem("New Viewport")) {
            ViewportManager::getInstance()->createViewport();
        }
        ImGui::EndMenu();
    }
}
