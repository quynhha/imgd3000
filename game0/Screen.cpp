#include "Screen.h"

#include "../Food.h"
#include "../Hero.h"
#include "../Saucer.h"
#include "../Points.h"
#include "Color.h"
#include "../Star.h"
#include "../Camera.h"
#include "../GameStart.h"
#include "EventKeyboard.h"
#include "../EnemyBlood.h"
#include "../vs-2017/Door.h"
#include "../Enemy.h"
#include "Music.h"

Screen::Screen()
{
    new Hero();

    for (int i = 0; i < 2; i++) {
        new Food();
    }
    for (int i = 0; i < 2; i++) {
        new Food("grape");
    }

    new Enemy();
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
