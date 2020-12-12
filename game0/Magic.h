#pragma once

#include "Object.h"
#include "EventCollision.h"

class Magic : public df::Object {

private:
    void out();
    void hit(const df::EventCollision* p_collision_event);

public:
    Magic(df::Vector hero_pos);
    int eventHandler(const df::Event* p_e);
};
