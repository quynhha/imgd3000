/*
GameStart.cpp
*/
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "LogManager.h"
#include "Saucer.h"
#include "Food.h"
#include "Hero.h"
#include "Points.h"
#include "Color.h"
#include "Star.h"
#include "Camera.h"
#include "GameStart.h"
#include "EventKeyboard.h"
#include "Enemy.h"
#include "Screen.h"
#include "Door.h"
#include "EnemyBlood.h"
#include "DisplayManager.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "LogManager.h"	
#include "WorldManager.h"

GameStart::GameStart() {
	//set Object Type
	setType("GameStart");
	//set sprites
	setSprite("forest");
   
    setLocation(df::CENTER_CENTER);

	registerInterest(df::KEYBOARD_EVENT);
    // Play start music.
    p_music = RM.getMusic("start music");
    
    playMusic();
}
GameStart::GameStart(df::Vector v)
{
    //set Object Type
    setType("GameStart");
    //set sprites
    setSprite("forest");

    setPosition(v);

    registerInterest(df::KEYBOARD_EVENT);
    // Play start music.
    p_music = RM.getMusic("start music");

    playMusic();
}
void GameStart::playMusic() {
    
        p_music->play();
    
}
int GameStart::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*) p_e;
        switch (p_keyboard_event->getKey()) {
        case df::Keyboard::P: 			// play
            start();
            break;
        case df::Keyboard::Q:			// quit
            GM.setGameOver();
            break;
        case df::Keyboard::ESCAPE:			// quit
            GM.setGameOver();
            break;
        default: // Key is not handled.
            break;
        }
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}
void GameStart::start() {

    df::ObjectList object_list = WM.getAllObjects(true);
    df::ObjectListIterator i(&object_list);
    for (i.first(); !i.isDone(); i.next()) {
        df::Object* p_o = i.currentObject();
        if (p_o->getType() == "Saucer" || p_o->getType() == "door"
            || p_o->getType() == "Enemy" || p_o->getType() == "Hero" ||
            p_o->getType() == "MagicFood" ||
            p_o->getType() == "Food" || p_o->getType() == "ViewObject") {
            WM.markForDelete(p_o);
        }
    }
    new Screen();
    //Pause start music.
    p_music->pause();
   
    // When game starts, become inactive.
    setActive(false);

}
int GameStart::draw() {
    return df::Object::draw();
}