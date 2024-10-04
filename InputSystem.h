#pragma once

#include <unordered_set>

#include "InputListener.h"

namespace engine
{
	class InputSystem
	{
	private:
		std::unordered_set<InputListener*> m_set_listeners;
		unsigned char m_keys_state[256] = {};
		unsigned char m_old_keys_state[256] = {};

	public:
		void update();
		void addListener(InputListener* listener);
		void removeListener(InputListener* listener);

	private:
		static InputSystem* P_SHARED_INSTANCE;

	private:
		InputSystem();
		~InputSystem();
		InputSystem(InputSystem const&);
		InputSystem& operator = (InputSystem const&);

	public:
		static InputSystem* getInstance();
		static void initialize();
		static void destroy();
	};

}

