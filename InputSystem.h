#pragma once

#include <unordered_set>

#include "InputListener.h"
#include "Vector2D.h"

namespace engine
{
	using namespace math;
	class InputSystem
	{
	private:
		std::unordered_set<InputListener*> setListeners;
		unsigned char keysState[256] = {};
		unsigned char oldKeysState[256] = {};

		Vector2D oldMousePosition;
		Vector2D deltaMousePosition;

		bool firstTime = true;
		bool shouldUpdate = true;

	public:
		void update();
		void stopUpdate();
		void startUpdate();
		void addListener(InputListener* listener);
		void removeListener(InputListener* listener);
		void setCursorPosition(const Vector2D& position);
		void showCursor(bool show);

		bool getKeyDown(int key);
		bool getKey(int key);
		bool getKeyUp(int key);
		Vector2D getDeltaMousePosition();
		Vector2D getMousePosition();

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

