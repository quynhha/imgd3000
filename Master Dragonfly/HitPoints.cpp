/*
HitPoints.cpp
*/

#include "Event.h"
#include "EventStep.h"
#include "LogManager.h"
#include "HitPoints.h"


// Define registerInterest in case engine does not.
static void registerInterest(std::string s) {};

HitPoints::HitPoints() {
	setLocation(df::TOP_CENTER);
	setViewString(HITPOINT_STRING);
	setColor(df::RED);
	// Need to update score each second, so count "step" events.
	registerInterest(df::STEP_EVENT);
	setType(HITPOINT_STRING);
	hp = 3;
}
int HitPoints::eventHandler(const df::Event* p_e) {
	// Parent handles event if score update.
	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}
	// If get here, have ignored this event.
	return 0;
}