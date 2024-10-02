#include "AppWindow.h"

using namespace application;

int main()
{
	AppWindow::initialize();
	AppWindow* runningApp = (AppWindow*)AppWindow::getInstance();
	runningApp->initializeEngine();

	while(runningApp->isRunning())
	{
		runningApp->broadcast();
	}

	return 0;
}