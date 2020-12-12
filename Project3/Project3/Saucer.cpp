/*
Saucer.cpp
*/
#include <stdlib.h>
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "DisplayManager.h"
#include "Saucer.h"
#include "EventOut.h"
#include "Explosion.h"
#include "EventCollision.h"
#include "EventNuke.h"
#include "Points.h"
#include "EventView.h"
#include "HitPoints.h"
#include "Hero.h"
#include "GameOver.h"
#include "Door.h"
#include "Food.h"


Saucer::Saucer(){
	

	// Setup "saucer" sprite.
	setSprite("saucer");
	
	// Set object type.
	setType("Saucer");

	// Set speed in horizontal direction.
	setVelocity(df::Vector(0, 0)); // 1 space left every 4 frames

	// Set starting location in the middle of window.
	moveToStart();

	registerInterest(NUKE_EVENT);
	
}
Saucer::~Saucer() {
	// Send "view" event with points to interested ViewObjects.
  // Add 10 points.
	df::EventView ev(POINTS_STRING, 10, true);
	WM.onEvent(&ev);
	//new Door();
	new Food("grape");
}

int Saucer::eventHandler(const df::Event* p_e)
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
		if (p_e->getType() == NUKE_EVENT) {
			// Create an explosion.
			Explosion* p_explosion = new Explosion;
			p_explosion->setPosition(this->getPosition());

			WM.markForDelete(this);
			// Saucers appear stay around perpetually.
			//new Saucer;
		}
	return 0;
}
void Saucer::out() {
	if (getPosition().getX() >= 0) 
		return;
	
	moveToStart();
	// Spawn new Saucer to make the game get harder.
	//new Saucer;
}
void Saucer::moveToStart() {
	df::Vector temp_pos;

	float world_horiz = WM.getBoundary().getHorizontal();
	float world_vert = WM.getBoundary().getVertical();

	// x is off right side of window
	temp_pos.setX(rand() % (int)world_horiz + 5.0f);
	// y is in vertical range.
	temp_pos.setY(rand() % (int)(world_vert ) + 4.0f);

	// If collision, move right slightly until empty space.
	df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
	while (!collision_list.isEmpty()) {
		temp_pos.setY(temp_pos.getY() + 1);
		collision_list = WM.getCollisions(this, temp_pos);
	}

	WM.moveObject(this, temp_pos);
}
void Saucer::hit(const df::EventCollision* p_c) {
	// If Saucer on Saucer, ignore.
	if ((p_c->getObject1()->getType() == "Saucer") &&
		(p_c->getObject2()->getType() == "Saucer")) {
		return;
	}
	// If Bullet...
	if ((p_c->getObject1()->getType() == "Bullet") ||
		(p_c->getObject2()->getType() == "Bullet")) {
		// Create an explosion.
		Explosion* p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());

		// Play "explode" sound.
		df::Sound* p_sound = RM.getSound("explode");
		p_sound->play();

		// Saucers appear stay around perpetually.
		//new Saucer;
	}

}