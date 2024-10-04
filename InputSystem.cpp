#include "InputSystem.h"
#include <Windows.h>

using namespace engine;

InputSystem* InputSystem::P_SHARED_INSTANCE = nullptr;

void InputSystem::update()
{
	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			// Key is down
			if (m_keys_state[i] & 0x80)
			{
				std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();
				while (it != m_set_listeners.end()) {
					(*it)->onKeyDown(i);
					++it;
				}
			}
			else // Key is up
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					std::unordered_set<InputListener*>::iterator it = m_set_listeners.begin();

					while (it != m_set_listeners.end())
					{
						(*it)->onKeyUp(i);
						++it;
					}
				}
			}
		}
		// Store current key state to old key state
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* listener)
{
	m_set_listeners.insert(listener);
}

void InputSystem::removeListener(InputListener* listener)
{
	m_set_listeners.erase(listener);
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