#include "ViewportScreen.h"

#include "imgui.h"

#include "AppWindow.h"
#include "CameraManager.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "imgui_internal.h"
#include "ViewportManager.h"

using namespace graphics;

ViewportScreen::ViewportScreen(int index) : UIScreen("Viewport " + std::to_string(index + 1)), index(index)
{
	this->currentCamera = new SceneCamera("Scene Camera " + std::to_string(index + 1));
	this->currentCamera->setPosition(0, 0, -3);
	this->currentCamera->setProjectionType(this->selectedProj);

	this->ownCamera = this->currentCamera;

	CameraManager::getInstance()->addSceneCamera(this->currentCamera);
	this->renderTexture = new RenderTexture();

	this->camIndex = index;

	this->selectedCameraIndex = this->camIndex;

	debug::Logger::log(this, "Initialized");
	debug::Logger::log(name + " Current Cam : " + currentCamera->getName());
}

ViewportScreen::~ViewportScreen()
{
	delete this->renderTexture;

	CameraManager::getInstance()->removeSceneCamera(this->ownCamera);
}

void ViewportScreen::draw()
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	renderSystem->getImmediateDeviceContext()->clearRenderTargetColor(this->renderTexture, 0.83, 0.58, 0.895, 1);

	ImGui::Begin(this->name.c_str(), &isActive, ImGuiWindowFlags_NoScrollbar);

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

	this->currentCamera->setWidth(viewportPanelSize.x);
	this->currentCamera->setHeight(viewportPanelSize.y);

	this->handleInput();

	this->currentCamera->update(EngineTime::getDeltaTime());

	if (!ImGui::IsWindowCollapsed() && viewportPanelSize.x > 0 && viewportPanelSize.y > 0)
	{
		renderSystem->getImmediateDeviceContext()->setViewportSize(viewportPanelSize.x, viewportPanelSize.y);

		this->renderTexture->resizeResources(viewportPanelSize.x, viewportPanelSize.y);
		AppWindow::getInstance()->draw(this->currentFillMode);
		renderSystem->getImmediateDeviceContext()->setRenderTarget(AppWindow::getInstance()->getSwapChain()->getRenderTexture());
	}

	this->drawViewportUI();
	viewportPanelSize = ImGui::GetContentRegionAvail();
	ImGui::Image((ImTextureID)this->renderTexture->getShaderResourceView(), viewportPanelSize);

	ImGui::End();

	RECT windowRect = AppWindow::getInstance()->getClientWindowRect();

	FLOAT width = windowRect.right - windowRect.left;
	FLOAT height = windowRect.bottom - windowRect.top;

	renderSystem->getImmediateDeviceContext()->setViewportSize(width, height);

	if (!isActive)
		ViewportManager::getInstance()->deleteViewport(this);
}

void ViewportScreen::handleInput()
{
	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

	if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow))
	{
		if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
		{
			InputSystem::getInstance()->addListener(this->currentCamera);
			this->currentCamera->setControllable(true);
			if (!ImGui::IsMouseHoveringRect(ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowPos().x + viewportPanelSize.x, ImGui::GetWindowPos().y + viewportPanelSize.y)))
			{
				InputSystem::getInstance()->removeListener(this->currentCamera);
				this->currentCamera->setControllable(false);
				ImGui::FocusWindow(NULL);

				// Floating Close button with a margin
				if (ImGui::Button("Close", ImVec2(100, 0)))
				{
					isActive = false;
				}
			}
		}
		if (ImGui::IsMouseReleased(ImGuiMouseButton_Right))
		{
			InputSystem::getInstance()->removeListener(this->currentCamera);
			this->currentCamera->setControllable(false);
		}
	}
}

void ViewportScreen::drawViewportUI()
{
	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

	float buttonWidth = viewportPanelSize.x / 8.0f;

	const char* perspectiveOptions[] = { "Perspective", "Orthographic", "Ortho Top" };

	const char* currentPersLabel = perspectiveOptions[selectedProj];

	ImGui::SetNextItemWidth(buttonWidth);
	if (ImGui::BeginCombo("##Perspective", currentPersLabel))
	{
		for (int n = 0; n < IM_ARRAYSIZE(perspectiveOptions); n++)
		{
			bool isSelected = (selectedProj == n);
			if (ImGui::Selectable(perspectiveOptions[n], isSelected))
			{
				selectedProj = n;
				this->currentCamera->setProjectionType(n);
				this->currentCamera->setPosition(0, 0, -3);
				this->currentCamera->setRotation(0, 0, 0);

				if (n == 2)
				{
					this->currentCamera->setPosition(0, 10, 0);
					this->currentCamera->setRotation(1.57f, 0, 0);
				}
			}
			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	const char* stateOptions[] = { "Solid", "Wireframe", "Solid Wireframe" };

	const char* currentStatesLabel = stateOptions[selectedState];

	ImGui::SameLine();
	ImGui::SetNextItemWidth(buttonWidth);
	if (ImGui::BeginCombo("##State", currentStatesLabel))
	{
		for (int n = 0; n < IM_ARRAYSIZE(perspectiveOptions); n++)
		{
			bool isSelected = (selectedState == n);
			if (ImGui::Selectable(stateOptions[n], isSelected))
			{
				selectedState = n;
				this->currentFillMode = static_cast<EFillMode>(n);
			}
			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	ImGui::SameLine();
	const auto& cameras = CameraManager::getInstance()->getSceneCameras();

	ImGui::SetNextItemWidth(buttonWidth);

	if (cameras.empty())
	{
		selectedCameraIndex = 0;
	}

	if (selectedCameraIndex >= cameras.size())
	{
		selectedCameraIndex = cameras.size() - 1;
	}

	std::string displayName = "Cam " + std::to_string(int(selectedCameraIndex + 1));
	if (ImGui::BeginCombo("##SelectCamera", displayName.c_str()))
	{
		for (size_t i = 0; i < cameras.size(); i++)
		{
			bool isSelected = (selectedCameraIndex == static_cast<int>(i));
			displayName = "Cam " + std::to_string(i + 1);
			if (ImGui::Selectable(displayName.c_str(), isSelected))
			{
				selectedCameraIndex = static_cast<int>(i);
				this->currentCamera->setControllable(false);
				this->currentCamera = cameras[selectedCameraIndex];
			}
			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
}
