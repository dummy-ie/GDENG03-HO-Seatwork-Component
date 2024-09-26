#include "AppWindow.h"

using namespace application;

int main()
{
	AppWindow app;
	if (app.init())
	{
		while(app.isRunning())
		{
			app.broadcast();
		}
	}
	return 0;
}