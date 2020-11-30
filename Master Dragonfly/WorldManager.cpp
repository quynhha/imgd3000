
//Thi Quynh Ha Nguyen - Dragonfly Master
/*
WorldManager.cpp
*/

#include "WorldManager.h"
#include "utility.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "ViewObject.h"

#include <stdio.h>
#include <stdlib.h>


// Default constructor
df::WorldManager::WorldManager()
{
	setType("WorldManager");
	//m_updates = *(new ObjectList());
	//m_deletions = *(new ObjectList());
}

df::WorldManager& df::WorldManager::getInstance()
{
	static df::WorldManager instance;

	return instance;
}

int df::WorldManager::startUp()
{
	m_updates.clear();
	m_deletions.clear();
	Manager::startUp();

	setViewFollowing(nullptr);
	setBoundary(Box(Vector(0, 0), DM.getHorizontal(), DM.getVertical()));
	setView(Box(Vector(0, 0), DM.getHorizontal(), DM.getVertical()));

	return Manager::startUp();
}

void df::WorldManager::shutDown()
{
	// Delete all game objects
	ObjectList ol = m_updates;	// copy list to delete by iteration
	ObjectListIterator li(&ol);
	for (li.first(); !li.isDone(); li.next())
	{
		delete li.currentObject();
	}

	Manager::shutDown();
}

int df::WorldManager::insertObject(Object *p_o)
{
	return m_updates.insert(p_o);
}

int df::WorldManager::removeObject(Object *p_o)
{
	if ((p_o != NULL) && (!m_updates.remove(p_o))) {
		//delete p_o;
		//p_o = NULL;
		return 0;
	}

	return 1;
}


df::ObjectList df::WorldManager::getAllObjects(bool inactive) const
{
	return m_updates;
}


df::ObjectList df::WorldManager::objectsOfType(std::string type) const
{
	ObjectList ol;
	ObjectListIterator li(&m_updates);
	for (li.first(); !li.isDone(); li.next()) {
		//if (li.currentObject()->getType().compare(type) == 0) {
		//	ol.insert(li.currentObject());
		//}
		if (std::strcmp(li.currentObject()->getType().c_str(), type.c_str())) {
			ol.insert(li.currentObject());
		}
	}

	return ol;
}


// Indicate Object is to be deleted at end of current game loop
// return 0 if successful
int df::WorldManager::markForDelete(Object *p_o)
{
	// Object might already be marked
	ObjectListIterator li(&m_deletions);
	while (!li.isDone()) {
		if (li.currentObject() == p_o) {
			return 0;
		}

		li.next();
	}

	m_deletions.insert(p_o);
	return 1;
}


// Update the world
void df::WorldManager::update()
{
	// Delete all marked objects
	ObjectListIterator liD(&m_deletions);
	while (!liD.isDone()) {
		delete liD.currentObject();
		liD.next();
	}

	m_deletions.clear();


	// Update object positions based on their velocities
	//Iterate through all objects
	ObjectListIterator liU(&m_updates);
	while (!liU.isDone()) {
		Object *p_temp_o = liU.currentObject();

		

		// Add velocity to position
		Vector new_pos = p_temp_o->predictPosition();

		// If object should change position then move it
		if(new_pos.getX() != p_temp_o->getPosition().getX() ||
			new_pos.getY() != p_temp_o->getPosition().getY()) {
			moveObject(p_temp_o, new_pos);
		}

		liU.next();
	}
}


void df::WorldManager::draw() {

	for (int alt = 0; alt <= MAX_ALTITUDE; alt++) {
		ObjectListIterator li(&m_updates);
		while (!li.isDone()) {
			Object *p_temp_o = li.currentObject();
			if (p_temp_o->getAltitude() == alt) {
				// Bounding box coordinates are relative to Object,
				// so convert to world coordinates
				Box temp_box = getWorldBox(p_temp_o);
				if (boxIntersectsBox(temp_box, view) || dynamic_cast <ViewObject *> (p_temp_o)) {
					p_temp_o->draw();
				}
			}
			li.next();
		}
	}
}


df::ObjectList df::WorldManager::isCollision(Object *p_o, Vector where) const {
	ObjectList collisionList;

	// Iterate through all aobjects
	ObjectListIterator li(&m_updates);
	while (!li.isDone()) {
		Object *p_temp_o = li.currentObject();

		
		
		// Make sure it does not consider itself
		if (p_temp_o != p_o) {

			// Same location and both solid?
			
			//LM.writeLog("Object Position: (%f, %f)", p_temp_o->getPosition().getX(), p_temp_o->getPosition().getY());
			//if (posititonsIntersect(p_temp_o->getPosition(), where) && (p_temp_o->isSolid())) {
			
			//World position bounding box for object at where
			Box b = getWorldBox(p_o, where);

			//World position bounding box for other object
			Box b_temp = getWorldBox(p_temp_o);

			if (boxIntersectsBox(b, b_temp) && p_temp_o->isSolid()) {
				collisionList.insert(p_temp_o);
			}

		}

		li.next();
	}

	return collisionList;
}


int df::WorldManager::moveObject(Object *p_o, Vector where) {
	if (p_o->isSolid()) {


		//Get Collisions
		ObjectList list = isCollision(p_o, where);

		if (!list.isEmpty()) {
			
			bool do_move = true; // Assume cna move

			// Iterate over list
			ObjectListIterator li(&list);
			while (!li.isDone()) {
				Object *p_temp_o = li.currentObject();
				
				// Create collison event
				EventCollision c(p_o, p_temp_o, where);

				// Send to both objects
				p_o->eventHandler(&c);
				p_temp_o->eventHandler(&c);

				// If both Hard, then cannot move
				if ((p_o->getSolidness() == HARD) && (p_temp_o->getSolidness() == HARD)) {
					do_move = false; // Cant move
				}

				li.next();
			}
			
			if (do_move == false) {
				return -1;
			}
		}

		if (p_view_following == p_o) {
			setViewPosition(p_o->getPosition());
		}

		p_o->setPosition(where);

		// Do this after the move call to prevent any loops of setting the position
		if (where.getX() < 0 || where.getX() > view.getHorizontal() - 1 ||
		where.getY() < 0 || where.getY() > view.getVertical() - 1) {
			EventOut o;
			p_o->eventHandler(&o);
		}

		return 0;
	}

	// Move
	Box orig_box = getWorldBox(p_o);
	p_o->setPosition(where);
	Box new_box = getWorldBox(p_o);

	if (boxIntersectsBox(orig_box, boundary) && (boxIntersectsBox(new_box, boundary))) {
		// Generate out of Bounds event and send to Object
		EventOut ov;
		p_o->eventHandler(&ov);
	}
	

	return 0;
}



int df::WorldManager::onEvent(const Event *p_event) const {
	return Manager::onEvent(p_event);
}

void df::WorldManager::setBoundary(Box new_boundary) {
	boundary = new_boundary;
}

df::Box df::WorldManager::getBoundary() const {
	return boundary;
}

void df::WorldManager::setView(Box new_view) {
	view = new_view;
}

df::Box df::WorldManager::getView() const {
	return view;
}

void df::WorldManager::setViewPosition(Vector view_pos) {
	// Make sure horizontal not out of boundary
	int x = view_pos.getX() - view.getHorizontal() / 2;

	if (x + view.getHorizontal() > boundary.getHorizontal()) {
		x = boundary.getHorizontal() - view.getHorizontal();
	}

	if (x < 0)
		x = 0;

	// Make sure horizontal not out of boundary
	int y = view_pos.getY() - view.getVertical() / 2;

	if (y + view.getVertical() > boundary.getVertical()) {
		y = boundary.getVertical() - view.getVertical();
	}

	if (y < 0)
		y = 0;

	//set view
	Vector new_corner(x, y);
	view.setCorner(new_corner);
}

int df::WorldManager::setViewFollowing(Object *p_new_view_following) {
	bool found = false;
	//set to null to turn 'off' following

	if (p_new_view_following == NULL) {
		p_view_following = NULL;
		return 0;
	}

	ObjectListIterator li = ObjectListIterator(&m_updates);

	//Delete all marked objects
	li.first();
	while (!li.isDone()) {
		if (li.currentObject() == p_new_view_following)
			found = true;
		li.next();
	}
	if (!found) {
		return -1;
	}

	p_view_following = p_new_view_following;
	setViewPosition(p_view_following->getPosition());
	return 0;
}