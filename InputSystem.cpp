#include "InputSystem.h"
#include <Windows.h>

using namespace engine;

InputSystem* InputSystem::P_SHARED_INSTANCE = nullptr;

void InputSystem::update()
{
	if (shouldUpdate)
	{
		POINT currentMousePosition = {};
		::GetCursorPos(&currentMousePosition);

		if (firstTime)
		{
			firstTime = false;
			oldMousePosition = Vector2D(currentMousePosition.x, currentMousePosition.y);
		}

		if (currentMousePosition.x != oldMousePosition.x || currentMousePosition.y != oldMousePosition.y)
		{
			std::unordered_set<InputListener*>::iterator it = setListeners.begin();
			while (it != setListeners.end()) {
				(*it)->onMouseMove(Vector2D(currentMousePosition.x - oldMousePosition.x, currentMousePosition.y - oldMousePosition.y));
				++it;
			}
		}

		oldMousePosition = Vector2D(currentMousePosition.x, currentMousePosition.y);

		if (::GetKeyboardState(keysState))
		{
			for (unsigned int i = 0; i < 256; i++)
			{
				// Key is down
				if (keysState[i] & 0x80)
				{
					std::unordered_set<InputListener*>::iterator it = setListeners.begin();
					while (it != setListeners.end()) {
						if (i == VK_LBUTTON)
						{
							if (keysState[i] != oldKeysState[i])
								(*it)->onLeftMouseDown(Vector2D(currentMousePosition.x, currentMousePosition.y));
						}
						else if (i == VK_RBUTTON)
						{
							if (keysState[i] != oldKeysState[i])
								(*it)->onRightMouseDown(Vector2D(currentMousePosition.x, currentMousePosition.y));
						}
						else
							(*it)->onKeyDown(i);

						++it;
					}
				}
				else // Key is up
				{
					if (keysState[i] != oldKeysState[i])
					{
						std::unordered_set<InputListener*>::iterator it = setListeners.begin();

						while (it != setListeners.end())
						{
							if (i == VK_LBUTTON)
								(*it)->onLeftMouseUp(Vector2D(currentMousePosition.x, currentMousePosition.y));
							else if (i == VK_RBUTTON)
								(*it)->onRightMouseUp(Vector2D(currentMousePosition.x, currentMousePosition.y));
							else
							(*it)->onKeyUp(i);
							++it;
						}
					}
				}
			}
			// Store current key state to old key state
			::memcpy(oldKeysState, keysState, sizeof(unsigned char) * 256);
		}
	}
}

void InputSystem::stopUpdate()
{
	shouldUpdate = false;
}

void InputSystem::startUpdate()
{
	shouldUpdate = true;
}

void InputSystem::addListener(InputListener* listener)
{
	setListeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	setListeners.erase(listener);
}

InputSystem::InputSystem() {}
InputSystem::~InputSystem() {}
InputSystem::InputSystem(const InputSystem&) {}

InputSystem* InputSystem::getInstance() {
	return P_SHARED_INSTANCE;
}

void InputSystem::initialize()
{
	P_SHARED_INSTANCE = new InputSystem();
	//P_SHARED_INSTANCE->init();
}

void InputSystem::destroy()
{
	if (P_SHARED_INSTANCE != nullptr)
	{
		//P_SHARED_INSTANCE->release();
	}
}