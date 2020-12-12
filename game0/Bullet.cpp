/*
Bullet.cpp
*/
#include "Bullet.h"
#include "Saucer.h"
#include <stdlib.h>
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "EventStep.h"


Bullet::Bullet(df::Vector hero_pos){
	// Link to "bullet" sprite.
	setSprite("bullet");

	// Set object type.
	setType("Bullet");
	
	// Set starting location, based on hero's position passed in.
	df::Vector p(hero_pos.getX() + 3, hero_pos.getY());
	setPosition(p);
	// Bullets move 1 space each game loop.
	// The direction is set when the Hero fires.
	setSpeed(1);
	// Note: in Bullet constructor
	// Make the Bullets soft so can pass through Hero.
	setSolidness(df::SOFT);
}
int Bullet::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0; 
}
void Bullet::out() {
	WM.markForDelete(this);
}

void Bullet::hit(const df::EventCollision* p_collision_event) {
	if ((p_collision_event->getObject1()->getType() == "Saucer") ||
		(p_collision_event->getObject2()->getType() == "Saucer")) {
		WM.markForDelete(p_collision_event->getObject1());
		WM.markForDelete(p_collision_event->getObject2());
	}
}