#include "ViewportManager.h"


ViewportManager* ViewportManager::P_SHARED_INSTANCE = NULL;

ViewportManager::ViewportManager()
{
}

ViewportManager::~ViewportManager()
{
}

ViewportManager::ViewportManager(const ViewportManager&) {}

ViewportManager* ViewportManager::getInstance()
{
	if (P_SHARED_INSTANCE == NULL)
		P_SHARED_INSTANCE = new ViewportManager();

	return P_SHARED_INSTANCE;
}

void ViewportManager::initialize()
{
	P_SHARED_INSTANCE = new ViewportManager();
}

void ViewportManager::destroy()
{
	delete P_SHARED_INSTANCE;
}

void ViewportManager::createViewport()
{
	ViewportScreen* viewport = new ViewportScreen(this->viewports.size() + 1);

	this->viewports.push_back(viewport);
	UIManager::getInstance()->addViewport(viewport);

	std::cout << "[VIEWPORT MANAGER] Viewports: " << this->viewports.size() << std::endl;
}

void ViewportManager::deleteViewport(ViewportScreen* viewport)
{
	int index = 0;
	for (int i = 0; i < this->viewports.size(); i++) 
	{
		if (this->viewports[i] == viewport) 
		{
			this->viewports.erase(this->viewports.begin() + index);
		}

		index++;
	}
}

std::vector<ViewportScreen*> ViewportManager::getViewports()
{
	return this->viewports;
}
