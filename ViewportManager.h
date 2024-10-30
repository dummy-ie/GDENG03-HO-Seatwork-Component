#pragma once
#include "ViewportScreen.h"
#include "UIManager.h"
#include <vector>
#include <iostream>

class ViewportManager
{
	private:
		ViewportManager();
		~ViewportManager();
		ViewportManager(const ViewportManager&);
		ViewportManager& operator=(const ViewportManager&);	

	private:
		std::vector<ViewportScreen*> viewports;

	public:
		static ViewportManager* getInstance();
		static void initialize();
		static void destroy();
		void update();
		
		void createViewport();
		void deleteViewport(ViewportScreen* viewport);
		void addViewport(UIScreen* viewport);
		std::vector<ViewportScreen*> getViewports();
		

	private:
		static ViewportManager* P_SHARED_INSTANCE;

};

