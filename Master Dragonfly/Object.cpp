//Thi Quynh Ha Nguyen - Dragonfly Master
/*
Object.cpp
*/

#include <string>

#include "Object.h"
#include "Vector.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "DisplayManager.h"

// Construct object. Set default params and
// add to game world (WorldManager)
df::Object::Object()
{
	position = Vector(0, 0);
	m_type = "Object";

	static int id_counter = 1;
	id = id_counter++;

	m_solidness = HARD;

	Box box = Box(getPosition(), 1, 1);
	sprite_slowdown = 0;
	sprite_slowdown_counter = 0;
	sprite_centered = false;
	
	m_altitude = MAX_ALTITUDE / 2;

	setSpriteIndex(0);

	speed = 0;
	direction = Vector(0, 0);
	setCentered(true);

	// Add self to game world
	WM.insertObject(this);
}

// Destroy object
// remove from game world (WorldManager)
df::Object::~Object()
{
	WM.removeObject(this);
	//delete this;
}

// set Object id
void df::Object::setId(int new_id) {
	id = new_id;
}

// get object id
int df::Object::getId() const {
	return id;
}

// set type identifier of object
void df::Object::setType(std::string new_type) {
	m_type = new_type;
}

// Get type identifier of object
std::string df::Object::getType() const {
	return m_type;
}

// set position of object
void df::Object::setPosition(Vector new_pos) {
	position = new_pos;
}

// get position of object
df::Vector df::Object::getPosition() const {
	return position;
}

int df::Object::eventHandler(const Event *p_e) {
	return 0;
}

void df::Object::draw() {

	//If sprite not defined, don't continue further
	if (p_sprite == NULL) {
		LM.writeLog("Sprite is null, could not draw!");
		return;
	}

	int index = getSpriteIndex();
	//Ask graphics manager to draw current frame

	//LM.writeLog("Sprite draw label: %s", p_sprite->getLabel().c_str());
	//LM.writeLog("Sprites pointer is: %p", p_sprite);

	DM.drawFrame(position, p_sprite->getFrame(index), sprite_centered, p_sprite->getColor());

	// test if animation frozen
	if (getSpriteSlowdown() == 0) {
		return;
	}

	int count = getSpriteSlowdownCounter();
	count++;

	if (count >= getSpriteSlowdown()) {
		count = 0; 
		index++;

		//if at last frame, loop to beginning
		if (index >= p_sprite->getFrameCount()) {
			index = 0;
		}
	}
	
	setSpriteSlowdownCounter(count);
	setSpriteIndex(index);
}

int df::Object::setAltitude(int new_altitude) {
	if ((new_altitude > 0) && (new_altitude <= MAX_ALTITUDE)) {
		m_altitude = new_altitude;
		return 0;
	}

	return 1;
}

int df::Object::getAltitude() const {
	return m_altitude;
}

df::Vector df::Object::predictPosition() {
	// Add velocity to position
	Vector new_pos = position + getVelocity();

	return new_pos;
}

void df::Object::setSpeed(float new_speed) {
	speed = new_speed;
}

float df::Object::getSpeed() const {
	return speed;
}

void df::Object::setDirection(Vector newDirection) {
	direction = newDirection;
}

df::Vector df::Object::getDirection() const {
	return direction;
}

void df::Object::setVelocity(Vector new_velocity) {
	speed = new_velocity.getMagnitude();
	direction = new_velocity;
	direction.normalize();
}

df::Vector df::Object::getVelocity() const {
	Vector vel;
	vel = direction;
	vel.scale(speed);

	return vel;
}

bool df::Object::isSolid() const {
	if (m_solidness == HARD || m_solidness == SOFT) {
		return true;
	}
	else {
		return false;
	}
}

int df::Object::setSolidness(Solidness new_solid) {
	m_solidness = new_solid;
	return 0;
}

df::Solidness df::Object::getSolidness() const {
	return m_solidness;
}



void df::Object::setSprite(Sprite *p_new_sprite, bool set_box) {
	p_sprite = p_new_sprite;
	box.setHorizontal(p_new_sprite->getWidth());
	box.setVertical(p_new_sprite->getHeight());
	box.setCorner(Vector((int)-(p_new_sprite->getWidth() / 2), (int)-(p_new_sprite->getHeight() / 2)));
}

df::Sprite *df::Object::getSprite() const {
	return p_sprite;
}

void df::Object::setCentered(bool centered) {
	sprite_centered = centered;
}

bool df::Object::isCentered() const {
	return sprite_centered;
}

void df::Object::setSpriteIndex(int new_sprite_index) {
	sprite_index = new_sprite_index;
}

int df::Object::getSpriteIndex() const {
	return sprite_index;
}

void df::Object::setSpriteSlowdown(int new_sprite_slowdown) {
	sprite_slowdown = new_sprite_slowdown;
}
int df::Object::getSpriteSlowdown() const {
	return sprite_slowdown;
}
void df::Object::setSpriteSlowdownCounter(int new_sprite_slowdown_count) {
	sprite_slowdown_counter = new_sprite_slowdown_count;
}
int df::Object::getSpriteSlowdownCounter() const {
	return sprite_slowdown_counter;
}

//Set object's bounding box
void df::Object::setBox(Box new_box) {
	box = new_box;
}
//Get Object's bounding box
df::Box df::Object::getBox() const {
	return box;
}