
//Thi Quynh Ha Nguyen - Dragonfly Master
/* 
EventStep.h
*/

#ifndef __EVENT_STEP_H__
#define __EVENT_STEP_H__

#include "Event.h"

namespace df {

	const std::string STEP_EVENT = "df::step";

	class EventStep : public Event {

	private:
		int step_count;     // Iteration number of game loops

	public:
		// Default constructor
		EventStep();

		// Constructor with initial step count
		EventStep(int init_step_count);

		// Set step count
		void setStepCount(int new_step_count);

		// Get step count
		int getStepCount() const;

	};

}; // End df namespace

#endif // __EVENT_STEP_H__