//Thi Quynh Ha Nguyen - Master Dragonfly
/*
EventKeyboard.cpp
*/

#include "EventKeyboard.h"
#include "LogManager.h"

df::EventKeyboard::EventKeyboard() {
	setType(KEYBOARD_EVENT);
}

void df::EventKeyboard::setKey(Keyboard::Key new_key) {
	m_key_val = new_key;
}

df::Keyboard::Key df::EventKeyboard::getKey() const {
	return m_key_val;
}

void df::EventKeyboard::setKeyboardAction(EventKeyboardAction new_action) {
	m_keyboard_action = new_action;
}

df::EventKeyboardAction df::EventKeyboard::getKeyboardAction() const {
	return m_keyboard_action;
}