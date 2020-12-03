/*
HitPoints.h
*/
#include "Event.h"
#include "ViewObject.h"
#define HITPOINT_STRING "HP"

class HitPoints : public df::ViewObject {
private:
    int hp;
public:
    HitPoints();
    int eventHandler(const df::Event* p_e);
};

