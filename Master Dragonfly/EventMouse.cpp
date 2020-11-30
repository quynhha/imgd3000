
//Thi Quynh Ha Nguyen - Dragonfly Master
// Purpose: Event when mouse action happens
// File:    EventMouse.cpp

#include "EventMouse.h"
#include "LogManager.h"

df::EventMouse::EventMouse() {
	setType(MOUSE_EVENT);
}

void df::EventMouse::setMouseAction(EventMouseAction new_mouse_action) {
	m_mouse_action = new_mouse_action;
}

df::EventMouseAction df::EventMouse::getMouseAction() const{
	return m_mouse_action;
}

void df::EventMouse::setMouseButton(Mouse::EventMouseButton new_mouse_button) {
	m_mouse_button = new_mouse_button;
}

df::Mouse::EventMouseButton df::EventMouse::getMouseButton() const {
	return m_mouse_button;
}

void df::EventMouse::setMousePosition(Vector new_mouse_xy) {
	m_mouse_xy = new_mouse_xy;
}

df::Vector df::EventMouse::getMousePosition() const {
	return m_mouse_xy;
}