#include "UIManager.h"

#include "ColorPickerScreen.h"
#include "CreditsScreen.h"
#include "EngineTime.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "DeviceContext.h"

#include "HierarchyScreen.h"
#include "imgui_internal.h"
#include "InspectorScreen.h"
#include "MenuScreen.h"
#include "ProfilerScreen.h"
#include "ViewportScreen.h"

using namespace graphics;

UIManager* UIManager::P_SHARED_INSTANCE = NULL;

int UIManager::RESIZE_WIDTH = 0;
int UIManager::RESIZE_HEIGHT = 0;

void UIManager::draw()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// Make Main Viewport into a Dock Space
	ImGuiID id = ImGui::GetID("Main Window");
	ImGui::DockSpaceOverViewport(id, ImGui::GetMainViewport());

	if (firstTime)
	{
		ImVec2 workCenter = ImGui::GetMainViewport()->GetWorkCenter();

		ImGui::DockBuilderRemoveNode(id);
		ImGui::DockBuilderAddNode(id);

		ImVec2 size{ WINDOW_WIDTH, WINDOW_HEIGHT };
		ImVec2 nodePos{ workCenter.x - size.x * 0.5f, workCenter.y - size.y * 0.5f };

		// Set the size and position:
		ImGui::DockBuilderSetNodeSize(id, size);
		ImGui::DockBuilderSetNodePos(id, nodePos);

		ImGuiID dock1 = ImGui::DockBuilderSplitNode(id, ImGuiDir_Right, 0.3f, nullptr, &id);
		ImGuiID dock2 = ImGui::DockBuilderSplitNode(dock1, ImGuiDir_Left, 0.5f, nullptr, &dock1);
		ImGuiID dock3 = ImGui::DockBuilderSplitNode(id, ImGuiDir_Left, 0.5f, nullptr, &id);
		ImGuiID dock4 = ImGui::DockBuilderSplitNode(dock3, ImGuiDir_Down, 0.25f, nullptr, &dock3);

		ImGui::DockBuilderDockWindow("Inspector", dock1);
		ImGui::DockBuilderDockWindow("Hierarchy", dock2);
		ImGui::DockBuilderDockWindow("Viewport", dock3);
		ImGui::DockBuilderDockWindow("Profiler", dock4);

		ImGui::DockBuilderFinish(id);

		firstTime = false;
		debug::Logger::log(this, "Initialized Dock Space on First Run");
	}

	for (UIScreen* screen : listUI)
	{
		if (screen->isActive)
			screen->draw();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

void UIManager::setActive(String name)
{
	this->mapUI[name]->setActive(true);
}

UIManager::UIManager(HWND hwnd)
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(renderSystem->getDirectXDevice(), renderSystem->getImmediateDeviceContext()->getContext());

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

	ViewportScreen* viewportScreen = new ViewportScreen();
	this->mapUI[uiNames.VIEWPORT_SCREEN] = viewportScreen;
	this->listUI.push_back(viewportScreen);

	debug::Logger::log(this, "Initialized");
}

UIManager::~UIManager()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	debug::Logger::log(this, "Destroyed");
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
