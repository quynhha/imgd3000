#include "EnemyBullet.h"
#include "Saucer.h"
#include <stdlib.h>
#include "LogManager.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "EventOut.h"
#include "EventStep.h"

void EnemyBullet::out()
{
	WM.markForDelete(this);
}

void EnemyBullet::hit(const df::EventCollision* p_collision_event)
{
	if ((p_collision_event->getObject1()->getType() == "Hero")) {
		WM.markForDelete(p_collision_event->getObject2());
	}if ((p_collision_event->getObject2()->getType() == "Hero")) {
		WM.markForDelete(p_collision_event->getObject1());
	}if ((p_collision_event->getObject1()->getType() == "Saucer")) {
		WM.markForDelete(p_collision_event->getObject2());
	}if ((p_collision_event->getObject2()->getType() == "Saucer")) {
		WM.markForDelete(p_collision_event->getObject1());
	}
	
}

EnemyBullet::EnemyBullet(df::Vector ene_pos)
{
	// Link to "bullet" sprite.
	setSprite("enebullet");

	// Set object type.
	setType("EnemyBullet");

	// Set starting location, based on hero's position passed in.
	df::Vector p(ene_pos.getX() + 4, ene_pos.getY());
	setPosition(p);
	// Bullets move 1 space each game loop.
	// The direction is set when the Hero fires.
	setSpeed(1);
	// Note: in Bullet constructor
	// Make the Bullets soft so can pass through Hero.
	setSolidness(df::HARD);
}

int EnemyBullet::eventHandler(const df::Event* p_e)
{
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
