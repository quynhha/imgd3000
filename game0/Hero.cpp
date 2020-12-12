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
#include "Bullet.h"
#include "EventOut.h"
#include "EventStep.h"
#include "EventNuke.h"
#include "EventView.h"
#include "GameOver.h"


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
	// Link to "ship" sprite.
	setSprite("ship");

	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::MSE_EVENT);
	// Set object type.
	setType("Hero");
	df::Vector p(7, WM.getBoundary().getVertical() / 2);
	setPosition(p);
	WM.setViewFollowing(this);
}
Hero::~Hero() {
	new GameOver;
	// Mark Reticle for deletion.
	WM.markForDelete(p_reticle);
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
		break;
	case df::Keyboard::W:    // up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			move(-1);
		break;
	case df::Keyboard::S:    // down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			move(+1);
		break;
	case df::Keyboard::SPACE:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			nuke();
		break;
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
		fire(p_mouse_event->getMousePosition());
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
	df::EventView ev("Nukes", -1, true);
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
	}
	//If it is Enemy, delete the hero
	if (((p_c->getObject1()->getType()) == "Enemy")|| 
		((p_c->getObject2()->getType()) == "Enemy")) {
		WM.markForDelete(p_c->getObject1());
		WM.markForDelete(p_c->getObject2());
		// Make a big explosion with particles.
		df::addParticles(df::SPARKS, getPosition(), 2, df::BLUE);
		df::addParticles(df::SPARKS, getPosition(), 2, df::YELLOW);
		df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
		df::addParticles(df::SPARKS, getPosition(), 3, df::RED);
		df::EventView ev("HP", -3, true);
		WM.onEvent(&ev);
		life_count == 0;
	}
	//If hero died more than 3
	if (life_count <= 0) {
		die();
	}
};