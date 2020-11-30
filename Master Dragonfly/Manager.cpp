//Thi Quynh Ha Nguyen - Dragonfly Master
/*
Manager.cpp
*/

#include "Manager.h"
#include "WorldManager.h"

// Basic constructor sets general type of manager
df::Manager::Manager()
{
	setType("Manager");
}

df::Manager::~Manager()
{

}

// Allows user to set the type of class, mainly used by child objects
void df::Manager::setType(std::string type)
{
	this->type = type;
}

// Allows access to the type field
std::string df::Manager::getType() const
{
	return type;
}

// child objects do alot of work here, for general purpose
// set the started flag to true
int df::Manager::startUp()
{
	is_started = true;
	return 0;
}

// Again children do work here, just set flag for now
void df::Manager::shutDown()
{
	is_started = false;
}

// Allows access to see if the class has been started
bool df::Manager::isStarted() const
{
	return is_started;
}

// Send event to all Objects
// Return count of number  of events sent
int df::Manager::onEvent(const Event *p_event) const 
{
	// Track the number of events sent
	int count = 0;

	// Get all the objects in the world and put them in object list ol
	df::WorldManager& world_manager = df::WorldManager::getInstance();
	ObjectList ol = world_manager.getAllObjects();

	// Iterate over all objects
	ObjectListIterator li(&ol);
	for (li.first(); !li.isDone(); li.next()) {
		li.currentObject()->eventHandler(p_event);
		count++;
	}

	// Return the number of events sent
	return count;
}