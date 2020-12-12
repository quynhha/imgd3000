#include "Food.h"
#include "LogManager.h"
#include "ResourceManager.h"
//game 
#include "Hero.h"
#include "EventView.h"
#include "Points.h"

// Define registerInterest in case engine does not.
static void registerInterest(std::string s) {};

Food::Food()
{
    setSprite("food");

    setType("Food");

    df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal() + 3.0f),
        (float)(rand() % (int)WM.getBoundary().getVertical()) + 4.0f);
    setPosition(p);
    //setPosition(p);
}

Food::Food(std::string label)
{
    setSolidness(df::SOFT);

    setSprite(label);

    setType("MagicFood");

    //interested in collisions
    registerInterest(df::COLLISION_EVENT);

    df::Vector p((float)(rand() % (int)WM.getBoundary().getHorizontal()),
        (float)(rand() % (int)WM.getBoundary().getVertical()));
    setPosition(p);
}
Food::~Food() {
    // Send "view" event with 50 points to interested ViewObjects.
    df::EventView ev(POINTS_STRING, 50, true);
    WM.onEvent(&ev);
}

int Food::eventHandler(const df::Event* p_e)
{
    //check collision
    if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
        found(p_collision_event);
    }
    return 0;
}

void Food::found(const df::EventCollision* p_collision_event)
{
    if (p_collision_event->getObject2()->getType() == "Enemy" )
    {
        WM.markForDelete(p_collision_event->getObject1()); 
        new Food();
    }if (p_collision_event->getObject1()->getType() == "Enemy" )
    {
        WM.markForDelete(p_collision_event->getObject2()); 
        new Food();
    }
    if (p_collision_event->getObject2()->getType() == "Magic")
    {
        //df::EventView ev("Hunger", +1, true);
        //WM.onEvent(&ev);
        WM.markForDelete(p_collision_event->getObject2());
    }if (p_collision_event->getObject1()->getType() == "Magic")
    {
       // df::EventView ev("Hunger", +1, true);
        //WM.onEvent(&ev);
        WM.markForDelete(p_collision_event->getObject1());
    }if (p_collision_event->getObject2()->getType() == "Bullet")
    {
       // df::EventView ev("Hunger", +1, true);
       // WM.onEvent(&ev);
        WM.markForDelete(p_collision_event->getObject2());
    }if (p_collision_event->getObject1()->getType() == "Bullet")
    {
        //df::EventView ev("Hunger", +1, true);
        //WM.onEvent(&ev);
        WM.markForDelete(p_collision_event->getObject1());
    }if (p_collision_event->getObject2()->getType() == "Hero")
    {
       df::EventView ev("Hunger", +1, true);
        WM.onEvent(&ev);
        WM.markForDelete(p_collision_event->getObject1());
    }if (p_collision_event->getObject1()->getType() == "Hero")
    {
        df::EventView ev("Hunger", +1, true);
        WM.onEvent(&ev);
        WM.markForDelete(p_collision_event->getObject2());
    }
        
    
}
