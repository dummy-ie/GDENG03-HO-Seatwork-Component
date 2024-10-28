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

	this->solidState = renderSystem->createRasterizerState(D3D11_FILL_SOLID, D3D11_CULL_BACK);
	this->wireframeState = renderSystem->createRasterizerState(D3D11_FILL_WIREFRAME, D3D11_CULL_NONE);
	debug::Logger::log(this, "Initialized");
}

ViewportScreen::~ViewportScreen()
{
	delete renderTexture;
}

void ViewportScreen::draw()
{
	RenderSystem* renderSystem = GraphicsEngine::getInstance()->getRenderSystem();
	DeviceContext* context = renderSystem->getImmediateDeviceContext();

	ImGui::Begin("Viewport", &isActive);

	ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

	renderTexture->resizeResources(viewportPanelSize.x, viewportPanelSize.y);
	AppWindow::getInstance()->drawOnRenderTexture(this->renderTexture);

	switch (currentFillMode)
	{
	default:
		context->setRasterizerState(solidState);
		break;
	case WIREFRAME:
		context->setRasterizerState(wireframeState);
		break;
	case SOLID_WIREFRAME:
		context->setRasterizerState(solidState);
		ImGui::Image((ImTextureID)renderTexture->getShaderResourceView(), viewportPanelSize);
		context->setRasterizerState(wireframeState);
		break;
	}

	ImGui::Image((ImTextureID)renderTexture->getShaderResourceView(), viewportPanelSize);

	ImGui::End();
}