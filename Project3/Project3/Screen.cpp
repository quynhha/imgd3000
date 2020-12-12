#include "Screen.h"

#include "Food.h"
#include "Hero.h"
#include "Saucer.h"
#include "Points.h"
#include "Color.h"
#include "Rock.h"
#include "Star.h"
#include "Camera.h"
#include "GameStart.h"
#include "EventKeyboard.h"
#include "EnemyBlood.h"
#include "EnemyMagicEvent.h"
#include "Door.h"
#include "Enemy.h"
#include "Music.h"
#include "DisplayManager.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "LogManager.h"	
#include "WorldManager.h"

Screen::Screen()
{

    new Hero();

    for (int i = 0; i < 2; i++) {
        new Food();
    }

    new Enemy(1,1);  

    for (int i = 0; i < 2 ; i++) {
        new Saucer();
    }
    new EnemyBlood(1);

    new EnemyMagicEvent(1);
    // Setup heads-up display.
    new Points;	// points display

    df::ViewObject* p_vo = new df::ViewObject; // Count of nukes.
    df::ViewObject* p_hp = new df::ViewObject; // Count of HPs.
    p_vo->setLocation(df::TOP_LEFT);
    p_vo->setViewString("Hunger");
    p_vo->setValue(10);
    p_vo->setColor(df::YELLOW);

    p_hp->setLocation(df::TOP_CENTER);
    p_hp->setViewString("HP");
    p_hp->setValue(3);
    p_hp->setColor(df::RED);
    
}

Screen::Screen(int a)
{
    df::ObjectList object_list = WM.getAllObjects(true);
    df::ObjectListIterator i(&object_list);
    for (i.first(); !i.isDone(); i.next()) {
        df::Object* p_o = i.currentObject();
        if (p_o->getType() == "Saucer" || p_o->getType() == "door1" || p_o->getType() == "door2" || p_o->getType() == "door3" || p_o->getType() == "door4"
            || p_o->getType() == "Enemy" || p_o->getType() == "Hero" ||
            p_o->getType() == "MagicFood" ||
            p_o->getType() == "Food" || p_o->getType() == "ViewObject")
            WM.markForDelete(p_o);
    }

    new Hero();

    for (int i = 0; i < 2; i++) {
        new Food();
    }

    new Enemy(a*5, (a+1) * 5);

    for (int i = 0; i < ((a + 1) * 5 + 2); i++) {
        new Saucer();
    }
    new EnemyBlood(a * 5);

    new EnemyMagicEvent((a + 1) * 5);
    // Setup heads-up display.
    new Points;	// points display

    df::ViewObject* p_vo = new df::ViewObject; // Count of nukes.
    df::ViewObject* p_hp = new df::ViewObject; // Count of HPs.
    p_vo->setLocation(df::TOP_LEFT);
    p_vo->setViewString("Hunger");
    p_vo->setValue(10);
    p_vo->setColor(df::YELLOW);

    p_hp->setLocation(df::TOP_CENTER);
    p_hp->setViewString("HP");
    p_hp->setValue(3);
    p_hp->setColor(df::RED);
}
