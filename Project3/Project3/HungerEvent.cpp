#include "HungerEvent.h"
#include "Event.h"
#include "EventStep.h"
#include "LogManager.h"


HungerEvent::HungerEvent() {
	setLocation(df::TOP_CENTER);
	setViewString(HUNGER);
	setColor(df::RED);
	// Need to update score each second, so count "step" events.
	registerInterest(df::STEP_EVENT);
	setType(HUNGER);
	hp = 3;
}
int HungerEvent::eventHandler(const df::Event* p_e) {
	// Parent handles event if score update.
	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	
	}

	// If get here, have ignored this event.
	return 0;
}