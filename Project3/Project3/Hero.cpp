/*
Hero.cpp
*/
#include <stdlib.h>
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "EventView.h"
#include "Hero.h"
#include "Rock.h"
#include "Bullet.h"
#include "Magic.h"
#include "EventOut.h"
#include "EventStep.h"
#include "EventNuke.h"
#include "EventView.h"
#include "GameOver.h"
#include "Screen.h"
#include "GameWin.h"


Hero::Hero() {
	// Create reticle for firing bullets.
	p_reticle = new Reticle();
	p_reticle->draw();
	move_slowdown = 2;
	move_countdown = move_slowdown;
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;
	nuke_count = 1;
	life_count = 3;
	hunger = 10; 
	magic_count = 0; 
	is_dead = false;
	// Link to "ship" sprite.
	setSprite("dog2");

	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::MSE_EVENT);
	// Set object type.
	setType("Hero");

	//df::Box boundary = WM.getBoundary();
	df::Vector p(7, WM.getBoundary().getVertical() / 2);
	setPosition(p);
	WM.setViewFollowing(this);
}
Hero::~Hero() {
	if (is_dead)
	{
		new GameOver(df::Vector(this->getPosition().getX(), WM.getBoundary().getVertical() / 2));
		// Mark Reticle for deletion.
		WM.markForDelete(p_reticle);
	}
	if (!is_dead)
	{
		if (door_num < 1 || door_num >= 5) {
			new GameOver(df::Vector(this->getPosition().getX(), WM.getBoundary().getVertical() / 2));
			// Mark Reticle for deletion.
			WM.markForDelete(p_reticle);
		}
		else
		{
			new Screen(door_num);
		}
	}
	
}
int Hero::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT)
	{
		if (dynamic_cast <const df::EventStep*> (p_e)
			->getStepCount() % 200 == 0) {
			df::EventView ev("Hunger", -1, true);
			WM.onEvent(&ev);
			hunger--;
			if (hunger <= 0)
			{
				df::EventView ev("HP", -1, true);
				WM.onEvent(&ev);
				life_count -= 1;
				hunger = 6;
				df::EventView ev1("Hunger", +6, true);
				WM.onEvent(&ev1);
				if (life_count <= 0) {
					die();
				}
			}
			if (hunger >= 11)
			{
				df::EventView ev("HP", +1, true);
				WM.onEvent(&ev);
				life_count += 1;
				hunger = 10;
				df::EventView ev1("Hunger", -1, true);
				WM.onEvent(&ev1);
				if (life_count <= 0) {
					die();
				}
			}
		}
		step();
		return 1;
	}
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event =
			dynamic_cast <const df::EventMouse*> (p_e);
		mouse(p_mouse_event);
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		// handle collisions with various other objects
		const df::EventCollision* p_collision_event =
			dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}
// Take appropriate action according to key pressed.
void Hero::kbd(const df::EventKeyboard* p_keyboard_event) {

	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::Q:			// quit
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			WM.markForDelete(this);
		break;case df::Keyboard::ESCAPE:			// quit
			if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
				GM.setGameOver();
		break;
	case df::Keyboard::W:    // up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			move(-3);
		break;
	case df::Keyboard::S:    // down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			move(+3);
		break;
	case df::Keyboard::A:    // up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			jump(-3);
		break;
	case df::Keyboard::D:    // down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			jump(+3);
		break;
	/*case df::Keyboard::SPACE:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			move(-4);
		}
		if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED) {
			move(+4);
		}
		break;
	case df::Keyboard::DOWNARROW:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			move(+4);
		}*/
	default:
		return;
	}
}
// Move up or down
void Hero::move(int dy) {
	// See if time to move.
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;
	// If stays on window, allow move.
	df::Vector new_pos(getPosition().getX(), getPosition().getY() + dy);
	// If stays on window, allow move.
	if ((new_pos.getY() > 3) &&
		(new_pos.getY() < WM.getBoundary().getVertical()))
		WM.moveObject(this, new_pos);
}
void Hero::jump(int dx) {
	// See if time to move.
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;
	// If stays on window, allow move.
	df::Vector new_pos(getPosition().getX() + dx, getPosition().getY());
	// If stays on window, allow move.
	if ((new_pos.getX() > 3) &&
		(new_pos.getX() < WM.getBoundary().getHorizontal()))
		WM.moveObject(this, new_pos);
}
void Hero::step() {
	// Move countdown.
	move_countdown--;
	if (move_countdown < 0)
		move_countdown = 0;
	// NOTE - in step()
	// Fire countdown.
	fire_countdown--;
	if (fire_countdown < 0)
		fire_countdown = 0;
}
// Take appropriate action according to mouse action.
void Hero::mouse(const df::EventMouse* p_mouse_event) {
	// Pressed button?
	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::LEFT))
		fire(df::Vector(this->getPosition().getX() + 4, this->getPosition().getY()));
		//fire(df::Vector(0, 0));

	if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::RIGHT))
		magic(df::Vector(this->getPosition().getX() + 4, this->getPosition().getY()));
}
void Hero::fire(df::Vector target) {
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;
	// Fire Bullet towards target.
	// Compute normalized vector to position, then scale by speed (1).
	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1);
	Bullet* p = new Bullet(getPosition());
	p->setVelocity(v);
	// Play "fire" sound.
	df::Sound* p_sound = RM.getSound("fire");
	p_sound->play();
}
void Hero::magic(df::Vector target) {
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;
	// Fire Bullet towards target.
	// Compute normalized vector to position, then scale by speed (1).
	if (magic_count > 0)
	{
		df::Vector v = target - getPosition();
		v.normalize();
		v.scale(1);
		Magic* p = new Magic(getPosition());
		p->setVelocity(v);
		// Play "fire" sound.
		df::Sound* p_sound = RM.getSound("fire");
		p_sound->play();
		magic_count--;
	}
	
}
//Nuke function
void Hero::nuke() {
	// Check if nukes left.
	if (!nuke_count)
		return;
	nuke_count--;
	// Create "nuke" event and send to interested Objects.
	EventNuke nuke;
	WM.onEvent(&nuke);
	// Send "view" event with nukes to interested ViewObjects.
	df::EventView ev("Hunger", -1, true);
	WM.onEvent(&ev);
	// Play "nuke" sound.
	df::Sound* p_sound = RM.getSound("nuke");
	p_sound->play();
}
//Function to kill the hero
void Hero::die() {
	// Make a big explosion with particles
	df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
	df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
	df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
	df::addParticles(df::SPARKS, getPosition(), 3, df::RED);

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
		df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
		df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
		df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
		df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
		df::EventView ev("HP", -1, true);
		WM.onEvent(&ev);
		life_count -= 1;
	}
	//If the one of the object collision is Saucer
	if (((p_c->getObject2()->getType()) == "Saucer")) {
		WM.markForDelete(p_c->getObject2());
		// Make a big explosion with particles.
		df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
		df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
		df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
		df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
		df::EventView ev("HP", -1, true);
		WM.onEvent(&ev);
		life_count -= 1;
	}if (((p_c->getObject1()->getType()) == "EnemyBullet")) {
		WM.markForDelete(p_c->getObject1());
		// Make a big explosion with particles.
		df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
		df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
		df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
		df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
		df::EventView ev("HP", -1, true);
		WM.onEvent(&ev);
		life_count -= 1;
	}
	//If the one of the object collision is Saucer
	if (((p_c->getObject2()->getType()) == "EnemyBullet")) {
		WM.markForDelete(p_c->getObject2());
		// Make a big explosion with particles.
		df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
		df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
		df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
		df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
		df::EventView ev("HP", -1, true);
		WM.onEvent(&ev);
		life_count -= 1;
	}
	//If it is Enemy, delete the hero
	if (((p_c->getObject1()->getType()) == "Enemy")) {
		WM.markForDelete(p_c->getObject2());
		// Make a big explosion with particles.
		df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
		df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
		df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
		df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
		//df::EventView ev("HP", -3, true);
		//WM.onEvent(&ev);
		life_count = 0;

	}if (p_c->getObject2()->getType() == "Enemy")
	{
		WM.markForDelete(p_c->getObject1());
		// Make a big explosion with particles.
		df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
		df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
		df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
		df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
		//df::EventView ev("HP", -3, true);
		//WM.onEvent(&ev);
		life_count = 0;
	}
	if (((p_c->getObject1()->getType()) == "Food") ||
		((p_c->getObject2()->getType()) == "Food")) {

		//df::EventView ev("Hunger", +1, true);
		//WM.onEvent(&ev);
		hunger++;
	}if (((p_c->getObject1()->getType()) == "MagicFood") ||
		((p_c->getObject2()->getType()) == "MagicFood")) {
	
		//df::EventView ev("Hunger", +1, true);
		//WM.onEvent(&ev);
		magic_count++;
		hunger++;
	}if (((p_c->getObject1()->getType()) == "door")|| 
		((p_c->getObject2()->getType()) == "door")) {
		WM.markForDelete(p_c->getObject1());
		WM.markForDelete(p_c->getObject2());
		door_num = 1;

	}if (((p_c->getObject1()->getType()) == "door1") ||
		((p_c->getObject2()->getType()) == "door1")) {
		WM.markForDelete(p_c->getObject1());
		WM.markForDelete(p_c->getObject2());
		door_num = 1;

	}if (((p_c->getObject1()->getType()) == "door2") ||
		((p_c->getObject2()->getType()) == "door2")) {
		WM.markForDelete(p_c->getObject1());
		WM.markForDelete(p_c->getObject2());
		door_num = 2;

	}
	if (((p_c->getObject1()->getType()) == "door3") ||
		((p_c->getObject2()->getType()) == "door3")) {
		WM.markForDelete(p_c->getObject1());
		WM.markForDelete(p_c->getObject2());
		door_num = 3;

	}
	if (((p_c->getObject1()->getType()) == "door4") ||
		((p_c->getObject2()->getType()) == "door4")) {
		WM.markForDelete(p_c->getObject1());
		WM.markForDelete(p_c->getObject2());
		door_num = 4;
	}
	
	//If hero died more than 3
	if (life_count <= 0) {
		is_dead = true;
		die();
	}
};