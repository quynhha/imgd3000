//Thi Quynh Ha Nguyen - Master Dragonfly
/*
InputManager.h
*/

#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include "Manager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

// Two-letter acronym for easier access to manager.
#define IM df::InputManager::getInstance()

namespace df {

	class InputManager : public Manager {

	private:
		InputManager();                     // Private since a singleton
		InputManager(InputManager const&);  // Don't allow copy
		void operator=(InputManager const&);// Don't allow assignment

		// converts sf mouse button to sf
		Mouse::EventMouseButton sfMouse2dfMouse(sf::Mouse::Button sfMouse);

		// converts sf keycodes to df
		Keyboard::Key sfKey2dfKey(sf::Keyboard::Key sfKey);

	public:
		// Get the one and only instance of the InputManager.
		static InputManager &getInstance();

		// Input manager only accepts keyboard and mouse events
		// Return false if not one of them
		bool isValid(std::string event_type) const;

		// Get window ready to capture input
		// Return 0 if ok, else return -1
		int startUp();

		// Revert back to normal window mode
		void shutDown();

		// Get input from the keyboard and mouse
		// Pass event along to all interested Objects
		void getInput();
	};

} // end of namespace df
#endif //__INPUT_MANAGER_H__
