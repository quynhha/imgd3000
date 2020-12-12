#pragma once
#include "Event.h"
#include "ViewObject.h"
#define HUNGER "Hunger"

class HungerEvent : public df::ViewObject {
private:
    int hp;
public:
    HungerEvent();
    int eventHandler(const df::Event* p_e);
};
