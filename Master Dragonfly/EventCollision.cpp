//Thi Quynh Ha Nguyen - Master Dragonfly
/*
EventCollision.cpp
*/

#include "EventCollision.h"


df::EventCollision::EventCollision() {
	setType(COLLISION_EVENT);
}

df::EventCollision::EventCollision(Object *p_o1, Object *p_o2, Vector p) {
	setType(COLLISION_EVENT);

	m_p_obj1 = p_o1;
	m_p_obj2 = p_o2;
	m_pos = p;
}

void df::EventCollision::setObject1(Object *p_new_o1) {
	m_p_obj1 = p_new_o1;
}

void df::EventCollision::setObject2(Object *p_new_o2) {
	m_p_obj2 = p_new_o2;
}

df::Object *df::EventCollision::getObject1() const {
	return m_p_obj1;
}

df::Object *df::EventCollision::getObject2() const {
	return m_p_obj2;
}

void df::EventCollision::setPosition(Vector new_pos) {
	m_pos = new_pos;
}

df::Vector df::EventCollision::getPosition() const {
	return m_pos;
}