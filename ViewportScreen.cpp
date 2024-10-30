#include "ViewportScreen.h"

#include "imgui.h"

#include "AppWindow.h"
#include "CameraManager.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "imgui_internal.h"

using namespace graphics;

ViewportScreen::ViewportScreen(int index) : UIScreen("Viewport " + std::to_string(index + 1)), index(index)
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();
	SceneCamera* camera = new SceneCamera(this->name + " Camera");
	camera->setPosition(0, 0, 0.5f);
	CameraManager::getInstance()->addSceneCamera(camera);
	this->currentCamera = CameraManager::getInstance()->getSceneCameraByIndex(index);
	this->renderTexture = new RenderTexture();

	this->camIndex = index;
	debug::Logger::log(this, "Initialized");
}

ViewportScreen::~ViewportScreen()
{
	delete this->renderTexture;
}

void ViewportScreen::draw()
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();
	renderSystem->getImmediateDeviceContext()->clearRenderTargetColor(this->renderTexture, 0.83, 0.58, 0.895, 1);

	ImGui::Begin(this->name.c_str(), &isActive, ImGuiWindowFlags_NoScrollbar);

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
			}
		}
		if (ImGui::IsMouseReleased(ImGuiMouseButton_Right))
		{
			InputSystem::getInstance()->removeListener(this->currentCamera);
			this->currentCamera->setControllable(false);
		}

		if (ImGui::IsKeyReleased(ImGuiKey_Q)) 
		{
			this->camIndex++;

			if (this->camIndex > CameraManager::getInstance()->getSceneCameras().size() - 1)
				this->camIndex = 0;

			this->currentCamera = CameraManager::getInstance()->getSceneCameraByIndex(this->camIndex);
		}

		if (ImGui::IsKeyReleased(ImGuiKey_E))
		{
			this->camIndex--;

			if (this->camIndex < 0)
				this->camIndex = CameraManager::getInstance()->getSceneCameras().size() - 1;

			this->currentCamera = CameraManager::getInstance()->getSceneCameraByIndex(this->camIndex);
		}
	}
	currentCamera->update(EngineTime::getDeltaTime());

	this->renderTexture->resizeResources(viewportPanelSize.x, viewportPanelSize.y);
	AppWindow::getInstance()->draw(this->currentFillMode);

	ImGui::Image((ImTextureID)this->renderTexture->getShaderResourceView(), viewportPanelSize);
	ImGui::End();

	renderSystem->getImmediateDeviceContext()->setRenderTarget(AppWindow::getInstance()->getSwapChain()->getRenderTexture());
}