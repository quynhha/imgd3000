
#ifndef DOOR_H
#define DOOR_H

#include "Event.h"
#include "EventCollision.h"
#include "Object.h"
#include "WorldManager.h"
#include "Vector.h"


class Door : public df::Object
{
private:

public:
	Door();
	Door(df::Vector v, int a);
	~Door();
	int eventHandler(const df::Event* p_e);
	void found(const df::EventCollision* p_collision_event);

};

#endif 
