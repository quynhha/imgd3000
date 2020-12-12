/*
GameStart.cpp
*/
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "LogManager.h"
#include "Saucer.h"
#include "Hero.h"
#include "Points.h"
#include "Color.h"
#include "Star.h"
#include "GameStart.h"
#include "EventKeyboard.h"
#include "Enemy.h"
#include "EnemyBlood.h"

GameStart::GameStart() {
	//set Object Type
	setType("GameStart");
	//set sprites
	setSprite("gamestart");

    setLocation(df::CENTER_CENTER);

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
        default: // Key is not handled.
            break;
        }
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}
void GameStart::start() {
    // Spawn some saucers to shoot.
    for (int i = 0; i < 14; i++)
        new Saucer();
    new Enemy();
    new Hero();
    // Setup heads-up display.
    new Points;	// points display
    df::ViewObject* p_vo = new df::ViewObject; // Count of nukes.
    df::ViewObject* p_hp = new df::ViewObject; // Count of HPs.
    p_vo->setLocation(df::TOP_LEFT);
    p_vo->setViewString("Nukes");
    p_vo->setValue(1);
    p_vo->setColor(df::YELLOW);
    p_hp->setLocation(df::TOP_CENTER);
    p_hp->setViewString("HP");
    p_hp->setValue(3);
    p_hp->setColor(df::RED);
    new EnemyBlood();
    // Pause start music.
    p_music->pause();
    // When game starts, become inactive.
    setActive(false);

}
int GameStart::draw() {
    return df::Object::draw();
}