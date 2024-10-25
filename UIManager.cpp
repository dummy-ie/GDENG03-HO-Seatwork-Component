#include "UIManager.h"

#include "ColorPickerScreen.h"
#include "CreditsScreen.h"
#include "EngineTime.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include "GraphicsEngine.h"
#include "HierarchyScreen.h"
#include "InspectorScreen.h"
#include "MenuScreen.h"
#include "ProfilerScreen.h"

using namespace engine::graphics;

UIManager* UIManager::P_SHARED_INSTANCE = NULL;

void UIManager::draw()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	

	for (UIScreen* screen : listUI)
	{
		if (screen->isActive)
			screen->draw();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::setActive(String name)
{
	this->mapUI[name]->setActive(true);
}

UIManager::UIManager(HWND hwnd)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(GraphicsEngine::getInstance()->getDirectXDevice(), GraphicsEngine::getInstance()->getImmediateDeviceContext()->getContext());

	UINames uiNames;
	MenuScreen* menuScreen = new MenuScreen();
	this->mapUI[uiNames.MENU_SCREEN] = menuScreen;
	this->listUI.push_back(menuScreen);

	CreditsScreen* creditsScreen = new CreditsScreen();
	this->mapUI[uiNames.CREDITS_SCREEN] = creditsScreen;
	this->listUI.push_back(creditsScreen);

	HierarchyScreen* hierarchyScreen = new HierarchyScreen();
	this->mapUI[uiNames.HIERARCHY_SCREEN] = hierarchyScreen;
	this->listUI.push_back(hierarchyScreen);

	InspectorScreen* inspectorScreen = new InspectorScreen();
	this->mapUI[uiNames.INSPECTOR_SCREEN] = inspectorScreen;
	this->listUI.push_back(inspectorScreen);

	ProfilerScreen* profilerScreen = new ProfilerScreen();
	this->mapUI[uiNames.PROFILER_SCREEN] = profilerScreen;
	this->listUI.push_back(profilerScreen);

	ColorPickerScreen* colorPickerScreen = new ColorPickerScreen();
	this->mapUI[uiNames.COLOR_PICKER_SCREEN] = colorPickerScreen;
	this->listUI.push_back(colorPickerScreen);
}

UIManager::UIManager(const UIManager&) {}

UIManager* UIManager::getInstance()
{
	return P_SHARED_INSTANCE;
}

void UIManager::initialize(HWND hwnd)
{
	P_SHARED_INSTANCE = new UIManager(hwnd);
}

void UIManager::destroy()
{
	delete P_SHARED_INSTANCE;
}
