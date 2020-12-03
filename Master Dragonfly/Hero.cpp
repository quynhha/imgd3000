//Thi Quynh Ha Nguyen - Dragonfly Master
// Hero.cpp
//

// Engine includes.
#include "EventMouse.h"
#include "EventStep.h"
#include "EventView.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include <Windows.h>

// Game includes.
#include "Bullet.h"
#include "EventNuke.h"
#include "Explosion.h"
#include "GameOver.h"
#include "Hero.h"

// Define registerInterest in case engine does not.
static void registerInterest(std::string s) {};

Hero::Hero() {

  // Link to "ship" sprite.
  df::Sprite *p_temp_sprite;
  p_temp_sprite = RM.getSprite("dog-idle");
  if (!p_temp_sprite)
    LM.writeLog("Hero::Hero(): Warning! Sprite '%s' not found", "ship");
  else {
    setSprite(p_temp_sprite);
    setSpriteSlowdown(3);  // 1/3 speed animation.
  }

  // Player controls hero, so register for input events.
  registerInterest(df::KEYBOARD_EVENT);
  registerInterest(df::MSE_EVENT);

  // Need to update rate control each step.
  registerInterest(df::STEP_EVENT);

  // Set object type.
  setType("Hero");

  // Set starting location.
  df::Vector p(7, WM.getBoundary().getVertical()/2);
  setPosition(p);

  // Create reticle for firing bullets.
  p_reticle = new Reticle();
  p_reticle->draw();

  // Set attributes that control actions.
  move_slowdown = 2;
  move_countdown = move_slowdown;
  fire_slowdown = 15;
  fire_countdown = fire_slowdown;
  nuke_count = 1;
  life_count = 3;
}
  
Hero::~Hero() {

	new GameOver;
	// Mark Reticle for deletion.
	WM.markForDelete(p_reticle);
}
 
// Handle event.
// Return 0 if ignored, else 1.
int Hero::eventHandler(const df::Event *p_e) {

  if (p_e->getType() == df::KEYBOARD_EVENT) {
    const df::EventKeyboard *p_keyboard_event = dynamic_cast <const df::EventKeyboard *> (p_e);
    kbd(p_keyboard_event);
    return 1;
  }

  if (p_e->getType() == df::MSE_EVENT) {
    const df::EventMouse *p_MSE_EVENT = dynamic_cast <const df::EventMouse *> (p_e);
    mouse(p_MSE_EVENT);
    return 1;
  }

  if (p_e->getType() == df::STEP_EVENT) {
    step();
    return 1;
  }

  if (p_e->getType() == df::COLLISION_EVENT) {
	  // handle collisions with various other objects
	  const df::EventCollision* p_collision_event =
		  dynamic_cast <df::EventCollision const*> (p_e);
	  hit(p_collision_event);
	  return 1;
  }
 
  // If get here, have ignored this event.
  return 0;
}

// Take appropriate action according to mouse action.
void Hero::mouse(const df::EventMouse *p_MSE_EVENT) {

  // Pressed button?
  if ((p_MSE_EVENT->getMouseAction() == df::CLICKED) &&
      (p_MSE_EVENT->getMouseButton() == df::Mouse::LEFT))
    fire(p_MSE_EVENT->getMousePosition());
}

// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard *p_keyboard_event) {

  switch(p_keyboard_event->getKey()) {
  case df::Keyboard::A:       //Walk left
    if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
      move(-1);
    break;
  case df::Keyboard::D:       // Walk right
    if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
      move(+1);
    break;
  case df::Keyboard::SPACE:   //jump
	  if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
		  jump(-2);
	  }
	  if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
		  jump(+2);
	  }
    break;
  case df::Keyboard::ESCAPE:        // quit
    if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
      WM.markForDelete(this);
    break;
  };

  return;
}

// Move up or down.
void Hero::move(int dx) {

  // See if time to move.
  if (move_countdown > 0)
    return;
  move_countdown = move_slowdown;

  // If stays on window, allow move.
  df::Vector new_pos(getPosition().getX() + dx, getPosition().getY());
  if ((new_pos.getX() > 3) && 
      (new_pos.getX() < WM.getBoundary().getHorizontal()-1))
    WM.moveObject(this, new_pos);
}

// Fire bullet towards target.
void Hero::fire(df::Vector target) {

  // See if time to fire.
  if (fire_countdown > 0)
    return;
  fire_countdown = fire_slowdown;

  // Fire Bullet towards target.
  Bullet *p = new Bullet(getPosition());
  p->setVelocity(df::Vector(p->getVelocity().getX(),
			    (target.getY() - getPosition().getY()) /
			    (target.getX() - getPosition().getX())));

  // Play "fire" sound.
  df::Sound *p_sound = RM.getSound("fire");
  p_sound->play();
}

// Decrease rate restriction counters.
void Hero::step() {

  // Move countdown.
  move_countdown--;
  if (move_countdown < 0)
    move_countdown = 0;

  // Fire countdown.
  fire_countdown--;
  if (fire_countdown < 0)
    fire_countdown = 0;
}

// Send "nuke" event to all objects.
void Hero::jump(int dy) {
	df::Vector old_pos(getPosition().getX(), getPosition().getY());
	
	df::Vector new_pos(getPosition().getX() , getPosition().getY() + dy );
	if ((new_pos.getY() > 3) &&
		(new_pos.getY() < WM.getBoundary().getVertical() - 1)){
		WM.moveObject(this, new_pos);
		Sleep(4);
	}

	///WM.moveObject(this, old_pos);
}

//Function to kill the hero
void Hero::die() {
	// Make a big explosion with particles

	// Play explosion sound
	df::Sound* p_sound = RM.getSound("explode");
	p_sound->play();

	// Remove the Boss
	WM.markForDelete(this);
}

//Check the collisions between Hero and other Objects
void Hero::hit(const df::EventCollision* p_c) {
	//If the one of the object collision is Saucer, don't delete Hero 
	if (((p_c->getObject1()->getType()) == "Saucer")) {
		WM.markForDelete(p_c->getObject1());
		// Make a big explosion with particles.
		df::EventView ev("HP", -1, true);
		WM.onEvent(&ev);
		life_count -= 1;
		// Play "explode" sound.
		df::Sound* p_sound = RM.getSound("explode");
		p_sound->play();
	}
	//If the one of the object collision is Saucer
	if (((p_c->getObject2()->getType()) == "Saucer")) {
		WM.markForDelete(p_c->getObject2());
		// Make a big explosion with particles.
		
		df::EventView ev("HP", -1, true);
		WM.onEvent(&ev);
		life_count -= 1;
		// Play "explode" sound.
		df::Sound* p_sound = RM.getSound("explode");
		p_sound->play();
	}
	
	//If hero died more than 3
	if (life_count <= 0) {
		die();
		// Play "explode" sound.
		df::Sound* p_sound = RM.getSound("explode");
		p_sound->play();
	}
};
