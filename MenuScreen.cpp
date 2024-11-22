#include "MenuScreen.h"

#include "ActionHistory.h"
#include "imgui.h"
#include "UIManager.h"
#include "GraphicsEngine.h"
#include "GameObjectManager.h"
#include "ViewportManager.h"

namespace GDEditor {
    using namespace GDEngine;
    MenuScreen::MenuScreen() : UIScreen("MenuScreen")
    {
        Logger::log(this, "Initialized");
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
            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Undo", "Ctrl+Z")) {
                    if (ActionHistory::getInstance()->hasRemainingUndoActions())
                    {
                        GameObjectManager::getInstance()->applyAction(ActionHistory::getInstance()->undoAction());
                    }
                    else Logger::log("Empty Undo");
                }
                if (ImGui::MenuItem("Redo", "Ctrl+Y")) {
                    if (ActionHistory::getInstance()->hasRemainingRedoActions())
                    {
                        GameObjectManager::getInstance()->applyAction(ActionHistory::getInstance()->redoAction());
                    }
                    else Logger::log("Empty Redo");
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Game Object")) {
                if (ImGui::BeginMenu("3D Object")) {
                    RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();
                    if (ImGui::BeginMenu("Primitives"))
                    {
                        if (ImGui::MenuItem("Cube")) {
                            GameObjectManager::getInstance()->createCube();
                        }
                        if (ImGui::MenuItem("Plane")) {
                            GameObjectManager::getInstance()->createPlane();
                        }
                        if (ImGui::MenuItem("Quad")) {
                            GameObjectManager::getInstance()->createQuad();
                        }
                        ImGui::EndMenu();
                    }
                    if (ImGui::BeginMenu("Textured Primitives"))
                    {
                        if (ImGui::MenuItem("Textured Cube")) {
                            GameObjectManager::getInstance()->createTexturedCube();
                        }
                        ImGui::EndMenu();
                    }
                    if (ImGui::BeginMenu("Models"))
                    {
                        if (ImGui::MenuItem("Teapot")) {
                            GameObjectManager::getInstance()->createTeapot();
                        }
                        if (ImGui::MenuItem("Bunny")) {
                            GameObjectManager::getInstance()->createBunny();
                        }
                        if (ImGui::MenuItem("Armadillo")) {
                            GameObjectManager::getInstance()->createArmadillo();
                        }
                        ImGui::EndMenu();
                    }
                    if (ImGui::BeginMenu("Physics Objects"))
                    {
                        if (ImGui::MenuItem("Physics Cube")) {
                            for (int i = 0; i < 20; i++)
                            {
                                GameObjectManager::getInstance()->createPhysicsCube();

                            }
                        }
                        if (ImGui::MenuItem("Physics Plane")) {
                            GameObjectManager::getInstance()->createPhysicsPlane();
                        }
                        ImGui::EndMenu();
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
                if (ImGui::BeginMenu("Viewport"))
                {
                    if (ImGui::MenuItem("Create Viewport"))
                    {
                        ViewportManager::getInstance()->createViewport();
                    }
                    if (ImGui::MenuItem("Single Viewport"))
                    {
                        ViewportManager::getInstance()->setNumViewports(1);
                    }
                    if (ImGui::MenuItem("2 Viewports"))
                    {
                        ViewportManager::getInstance()->setNumViewports(2);
                    }
                    if (ImGui::MenuItem("3 Viewports"))
                    {
                        ViewportManager::getInstance()->setNumViewports(3);
                    }
                    if (ImGui::MenuItem("4 Viewports"))
                    {
                        ViewportManager::getInstance()->setNumViewports(4);
                    }
                    if (ImGui::MenuItem("Delete All Viewports"))
                    {
                        ViewportManager::getInstance()->deleteAllViewports();
                    }
                    ImGui::EndMenu();
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
}