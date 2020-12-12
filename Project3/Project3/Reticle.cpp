/*
Reticle.cpp
*/

#include "Reticle.h"
#include <stdlib.h>
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "EventMouse.h"
#include "DisplayManager.h"

Reticle::Reticle() {

	// Set object type.
	setType("Reticle");

	setSolidness(df::SPECTRAL);

	registerInterest(df::MSE_EVENT);

	setAltitude(df::MAX_ALTITUDE); // Make Reticle in foreground.

	// Start reticle in center of window.
	df::Vector p(WM.getBoundary().getHorizontal() / 2, WM.getBoundary().getVertical() / 2);
	setPosition(p);
}

int Reticle::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event =
			dynamic_cast <const df::EventMouse*> (p_e);
		if (p_mouse_event->getMouseAction() == df::MOVED) {
			// Change location to new mouse position.
			setPosition(df::Vector(p_mouse_event->getMousePosition().getX(), WM.getBoundary().getVertical() / 2));
			return 1;
		}
	}

	// If get here, have ignored this event.
	return 0;
}
// Draw reticle on window.
int Reticle::draw() {
	return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
}