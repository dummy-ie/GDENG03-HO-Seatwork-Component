#include "MenuScreen.h"

#include "imgui.h"
#include "UIManager.h"
#include "GraphicsEngine.h"
#include "GameObjectManager.h"

MenuScreen::MenuScreen() : UIScreen("MenuScreen")
{
}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::draw()
{
	if (ImGui::BeginMainMenuBar())
	{
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Create")) {
            }
            if (ImGui::MenuItem("Open", "Ctrl+O")) {
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {
            }
            if (ImGui::MenuItem("Save as..")) {
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Game Object")) {
            if (ImGui::BeginMenu("3D Object")) {
                if (ImGui::MenuItem("Cube")) {
                    void* shaderByteCode = nullptr;
                    size_t sizeShader = 0;

                    GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
                    VertexShader* vertexShader = GraphicsEngine::getInstance()->createVertexShader(shaderByteCode, sizeShader);

                    GameObjectManager::getInstance()->createCube(shaderByteCode, sizeShader);

                    vertexShader->release();
                }
                if (ImGui::MenuItem("Plane")) {
                    void* shaderByteCode = nullptr;
                    size_t sizeShader = 0;

                    GraphicsEngine::getInstance()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
                    VertexShader* vertexShader = GraphicsEngine::getInstance()->createVertexShader(shaderByteCode, sizeShader);

                    GameObjectManager::getInstance()->createPlane(shaderByteCode, sizeShader);

                    vertexShader->release();
                }
                if (ImGui::MenuItem("Quad")) {
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Window")) {
            if (ImGui::MenuItem("Inspector")) {
                UIManager::getInstance()->setActive("INSPECTOR_SCREEN");
            }
            if (ImGui::MenuItem("Hierarchy")) {
                UIManager::getInstance()->setActive("HIERARCHY_SCREEN");
            }
            if (ImGui::MenuItem("Profiler")) {
                UIManager::getInstance()->setActive("PROFILER_SCREEN");
            }
            if (ImGui::MenuItem("Color Picker")) {
                UIManager::getInstance()->setActive("COLOR_PICKER_SCREEN");
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::BeginMenu("About")) {
                if (ImGui::MenuItem("Credits")) {
                    UIManager::getInstance()->setActive("CREDITS_SCREEN");
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
		ImGui::EndMainMenuBar();
	}
}
