#include "Door.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "EventView.h"
//#include "Explosion.h"
#include "../Points.h"

Door::Door()
{
    setSprite("door");

    setType("door");

    //interested in collisions
    registerInterest(df::COLLISION_EVENT);

    df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
        (float)(rand() % (int)WM.getBoundary().getVertical()));
    setPosition(p);
}

Door::~Door()
{
    df::EventView ev(POINTS_STRING, 500, true);
    WM.onEvent(&ev);


}

int Door::eventHandler(const df::Event* p_e)
{
    //check collision
    if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
        found(p_collision_event);
    }
    return 0;
}

void Door::found(const df::EventCollision* p_collision_event)
{
    if (p_collision_event->getObject1()->getType() == "Hero"){
        WM.markForDelete(p_collision_event->getObject2());

    }
    if (p_collision_event->getObject2()->getType() == "Hero") {
        WM.markForDelete(p_collision_event->getObject1());
    }
    
}
