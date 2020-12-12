#pragma once

#ifndef FOOD_H
#define FOOD_H

#include "Event.h"
#include "EventCollision.h"
#include "Object.h"
#include "WorldManager.h"
#include "Vector.h"


class Food : public df::Object
{
private:

public: 
	Food();
	Food(std::string label);
	~Food();
	int eventHandler(const df::Event* p_e);
	void found(const df::EventCollision* p_collision_event);

};

#endif 