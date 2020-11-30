//Thi Quynh Ha Nguyen - Master Dragonfly
/* 
Manager.cpp
*/


#include "InputManager.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "GameManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"

// Basic constructor sets general type of manager
df::InputManager::InputManager()
{
	setType("InputManager");
}

// Get the singleton instance of GameManager
df::InputManager& df::InputManager::getInstance()
{
	static df::InputManager instance;

	return instance;
}



int df::InputManager::startUp()
{
	if (DM.isStarted() == false) {
		LM.writeLog("Failed to start InputManager, no InputManager found!");
		return 1;
	}

	sf::RenderWindow *p_window = DM.getWindow();
	p_window->setKeyRepeatEnabled(false);

	return Manager::startUp();
}

// Again children do work here, just set flag for now
void df::InputManager::shutDown()
{
	if (DM.isStarted() == false) {
		LM.writeLog("Failed to stop InputManager, no InputManager found!");
	}

	sf::RenderWindow *p_window = DM.getWindow();
	p_window->setKeyRepeatEnabled(true);

	Manager::shutDown();
}



void df::InputManager::getInput() {
	//Check past window events
	sf::RenderWindow *p_window = DM.getWindow();
	sf::Event event;
	while (p_window->pollEvent(event)) {
		// Key was pressed
		if (event.type == sf::Event::KeyPressed) {
			EventKeyboard k;
			k.setKeyboardAction(KEY_PRESSED);
			k.setKey(sfKey2dfKey(event.key.code));
			onEvent(&k);
		}

		// Key was released
		if (event.type == sf::Event::KeyReleased) {
			EventKeyboard k;
			k.setKeyboardAction(KEY_RELEASED);
			k.setKey(sfKey2dfKey(event.key.code));
			onEvent(&k);
		}

		// Mouse was moved
		if (event.type == sf::Event::MouseMoved) {
			EventMouse m;
			m.setMouseAction(MOVED);
			Vector mousePos = Vector(event.mouseMove.x, event.mouseMove.y);
			m.setMousePosition(df::pixelsToSpaces(mousePos));
			onEvent(&m);
		}

		// Mouse was clicked
		if (event.type == sf::Event::MouseButtonPressed) {
			EventMouse m;
			m.setMouseAction(CLICKED);
			Vector mousePos = Vector(event.mouseButton.x, event.mouseButton.y);
			m.setMousePosition(df::pixelsToSpaces(mousePos));
			m.setMouseButton(sfMouse2dfMouse(event.mouseButton.button));
			onEvent(&m);
		}
		if (event.type == sf::Event::Closed)
		{
			GM.setGameOver();
			return;
		}
	}

	// Key is pressed
	for (int keyCode = -1; keyCode < sf::Keyboard::KeyCount; keyCode++) {
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)keyCode)) {
			EventKeyboard k;
			k.setKeyboardAction(KEY_DOWN);
			k.setKey(sfKey2dfKey((sf::Keyboard::Key)keyCode));
			onEvent(&k);
		}
	}

	// Mouse is pressed
	for (int button = 0; button < sf::Mouse::ButtonCount; button++) {
		if (sf::Mouse::isButtonPressed((sf::Mouse::Button)button)) {
			EventMouse m;
			m.setMouseAction(PRESSED);
			Vector mousePos = Vector(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
			m.setMousePosition(df::pixelsToSpaces(mousePos));
			m.setMouseButton(sfMouse2dfMouse((sf::Mouse::Button)button));
			onEvent(&m);
		}
	}

}

df::Mouse::EventMouseButton df::InputManager::sfMouse2dfMouse(sf::Mouse::Button sfMouse) {
	switch (sfMouse)
	{
	case sf::Mouse::Left:
		return df::Mouse::LEFT;
		break;
	case sf::Mouse::Right:
		return df::Mouse::RIGHT;
		break;
	case sf::Mouse::Middle:
		return df::Mouse::MIDDLE;
		break;
	case sf::Mouse::XButton1:
	case sf::Mouse::XButton2:
	case sf::Mouse::ButtonCount:
	default:
		return df::Mouse::UNDEFINED_MOUSE_BUTTON;
		break;
	}
}


df::Keyboard::Key df::InputManager::sfKey2dfKey(sf::Keyboard::Key sfKey) {
	switch (sfKey)
	{
	case sf::Keyboard::A:
		return df::Keyboard::A;
	case sf::Keyboard::B:
		return df::Keyboard::B;
	case sf::Keyboard::C:
		return df::Keyboard::C;
	case sf::Keyboard::D:
		return df::Keyboard::D;
	case sf::Keyboard::E:
		return df::Keyboard::E;
	case sf::Keyboard::F:
		return df::Keyboard::F;
	case sf::Keyboard::G:
		return df::Keyboard::G;
	case sf::Keyboard::H:
		return df::Keyboard::H;
	case sf::Keyboard::I:
		return df::Keyboard::I;
	case sf::Keyboard::J:
		return df::Keyboard::J;
	case sf::Keyboard::K:
		return df::Keyboard::K;
	case sf::Keyboard::L:
		return df::Keyboard::L;
	case sf::Keyboard::M:
		return df::Keyboard::M;
	case sf::Keyboard::N:
		return df::Keyboard::N;
	case sf::Keyboard::O:
		return df::Keyboard::O;
	case sf::Keyboard::P:
		return df::Keyboard::P;
	case sf::Keyboard::Q:
		return df::Keyboard::Q;
	case sf::Keyboard::R:
		return df::Keyboard::R;
	case sf::Keyboard::S:
		return df::Keyboard::S;
	case sf::Keyboard::T:
		return df::Keyboard::T;
	case sf::Keyboard::U:
		return df::Keyboard::U;
	case sf::Keyboard::V:
		return df::Keyboard::V;
	case sf::Keyboard::W:
		return df::Keyboard::W;
	case sf::Keyboard::X:
		return df::Keyboard::X;
	case sf::Keyboard::Y:
		return df::Keyboard::Y;
	case sf::Keyboard::Z:
		return df::Keyboard::Z;
	case sf::Keyboard::Num0:
		return df::Keyboard::NUM0;
	case sf::Keyboard::Num1:
		return df::Keyboard::NUM1;
	case sf::Keyboard::Num2:
		return df::Keyboard::NUM2;
	case sf::Keyboard::Num3:
		return df::Keyboard::NUM3;
	case sf::Keyboard::Num4:
		return df::Keyboard::NUM4;
	case sf::Keyboard::Num5:
		return df::Keyboard::NUM5;
	case sf::Keyboard::Num6:
		return df::Keyboard::NUM6;
	case sf::Keyboard::Num7:
		return df::Keyboard::NUM7;
	case sf::Keyboard::Num8:
		return df::Keyboard::NUM8;
	case sf::Keyboard::Num9:
		return df::Keyboard::NUM9;
	case sf::Keyboard::BackSpace:
		return df::Keyboard::BACKSPACE;
	case sf::Keyboard::F1:
		return df::Keyboard::F1;
	case sf::Keyboard::F2:
		return df::Keyboard::F2;
	case sf::Keyboard::F3:
		return df::Keyboard::F3;
	case sf::Keyboard::F4:
		return df::Keyboard::F4;
	case sf::Keyboard::F5:
		return df::Keyboard::F5;
	case sf::Keyboard::F6:
		return df::Keyboard::F6;
	case sf::Keyboard::F7:
		return df::Keyboard::F7;
	case sf::Keyboard::F8:
		return df::Keyboard::F8;
	case sf::Keyboard::F9:
		return df::Keyboard::F9;
	case sf::Keyboard::F10:
		return df::Keyboard::F10;
	case sf::Keyboard::F11:
		return df::Keyboard::F11;
	case sf::Keyboard::F12:
		return df::Keyboard::F12;
	case sf::Keyboard::Space:
		return df::Keyboard::SPACE;
	case sf::Keyboard::Return:
		return df::Keyboard::RETURN;
	case sf::Keyboard::Escape:
		return df::Keyboard::ESCAPE;
	case sf::Keyboard::Tab:
		return df::Keyboard::TAB;
	case sf::Keyboard::Left:
		return df::Keyboard::LEFTARROW;
	case sf::Keyboard::Right:
		return df::Keyboard::RIGHTARROW;
	case sf::Keyboard::Up:
		return df::Keyboard::UPARROW;
	case sf::Keyboard::Down:
		return df::Keyboard::DOWNARROW;
	case sf::Keyboard::Pause:
		return df::Keyboard::PAUSE;
	case sf::Keyboard::Subtract:
		return df::Keyboard::MINUS;
	case sf::Keyboard::Add:
		return df::Keyboard::PLUS;
	case sf::Keyboard::Tilde:
		return df::Keyboard::TILDE;
	case sf::Keyboard::Period:
		return df::Keyboard::PERIOD;
	case sf::Keyboard::Comma:
		return df::Keyboard::COMMA;
	case sf::Keyboard::Slash:
		return df::Keyboard::SLASH;
	case sf::Keyboard::Equal:
		return df::Keyboard::EQUAL;
	case sf::Keyboard::BackSlash:
		return df::Keyboard::BACKSLASH;
	case sf::Keyboard::Multiply:
		return df::Keyboard::MULTIPLY;
	case sf::Keyboard::Quote:
		return df::Keyboard::QUOTE;
	case sf::Keyboard::SemiColon:
		return df::Keyboard::SEMICOLON;
	case sf::Keyboard::LControl:
		return df::Keyboard::LEFTCONTROL;
	case sf::Keyboard::RControl:
		return df::Keyboard::RIGHTCONTROL;
	case sf::Keyboard::LShift:
		return df::Keyboard::LEFTSHIFT;
	case sf::Keyboard::RShift:
		return df::Keyboard::RIGHTSHIFT;
	case sf::Keyboard::Unknown:
	default:
		return df::Keyboard::UNDEFINED_KEY;
		break;
	}
}