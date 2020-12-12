/*
GameOver.cpp
*/
#include "GameOver.h"
#include <stdlib.h>
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventView.h"
#include "EventOut.h"
#include "EventStep.h"
#include "GameStart.h"
#include "Music.h"

GameOver::GameOver() {
	//set Type
	setType("GameOver");
	
	//Set Sprite
	// Link to "message" sprite.
	if (setSprite("gameover") == 0)
		time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
	else
		time_to_live = 0;

	// Put in center of window.
	setLocation(df::CENTER_CENTER);

	// Register for step event.
	registerInterest(df::STEP_EVENT);
	// Play "game over" sound.
	df::Sound* p_sound = RM.getSound("game over");
	p_sound->play();
}
GameOver::GameOver(df::Vector v)
{
	//set Type
	setType("GameOver");

	//Set Sprite
	// Link to "message" sprite.
	if (setSprite("gameover") == 0)
		time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
	else
		time_to_live = 0;

	// Put in center of window.
	setPosition(v);

	// Register for step event.
	registerInterest(df::STEP_EVENT);
	// Play "game over" sound.
	df::Sound* p_sound = RM.getSound("game over");
	p_sound->play();
}
GameOver::~GameOver() {
	// Remove Saucers and ViewObjects, re-activate GameStart.
	df::ObjectList object_list = WM.getAllObjects(true);
	df::ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next()) {
		df::Object* p_o = i.currentObject();
		if (p_o->getType() == "Saucer" || p_o->getType() == "door1" || p_o->getType() == "door2" || p_o->getType() == "door3" || p_o->getType() == "door4" 
			||p_o->getType() == "Enemy" || p_o->getType() == "Hero" || 
			p_o->getType() == "MagicFood" ||
			p_o->getType() == "Food" || p_o->getType() == "ViewObject")
			WM.markForDelete(p_o);
		if (p_o->getType() == "GameStart") {
			//p_o->setActive(true);
			WM.markForDelete(p_o);
			//dynamic_cast <GameStart*> (p_o)->playMusic(); // Resume start music.
			new GameStart(this->getPosition());
		}
	}

}
int GameOver::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT)
	{
		step();
		return 1;
	}

	return 0;
}
// Count down to end of message.
void GameOver::step() {
	time_to_live--;
	if (time_to_live <= 0)
		WM.markForDelete(this);
}
// Override default draw so as not to display "value".
int GameOver::draw() {
	return df::Object::draw();
}