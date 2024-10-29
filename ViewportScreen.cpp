#include "ViewportScreen.h"

#include "imgui.h"

#include "AppWindow.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "imgui_internal.h"

using namespace graphics;

ViewportScreen::ViewportScreen() : UIScreen("Viewport")
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();

	this->renderTexture = new RenderTexture();

	debug::Logger::log(this, "Initialized");
}

ViewportScreen::~ViewportScreen()
{
	delete renderTexture;
}

void ViewportScreen::draw()
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();
	renderSystem->getImmediateDeviceContext()->clearRenderTargetColor(renderTexture, 0.83, 0.58, 0.895, 1);

	ImGui::Begin("Viewport", &isActive);

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
	renderTexture->resizeResources(viewportPanelSize.x, viewportPanelSize.y);
	AppWindow::getInstance()->draw(this->currentFillMode);

	ImGui::Image((ImTextureID)renderTexture->getShaderResourceView(), viewportPanelSize);
	ImGui::End();

	renderSystem->getImmediateDeviceContext()->setRenderTarget(AppWindow::getInstance()->getSwapChain()->getRenderTexture());
}