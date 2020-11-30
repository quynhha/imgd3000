
//Thi Quynh Ha Nguyen - Dragonfly Master
/*
Box.cpp
*/

#include "Box.h"

df::Box::Box() {
	m_corner = Vector(0, 0);
	m_horizontal = 0;
	m_vertical = 0;
}

df::Box::Box(Vector init_corner, float init_horizontal, float init_vertical) {
	m_corner = init_corner;
	m_horizontal = init_horizontal;
	m_vertical = init_vertical;
}

void df::Box::setCorner(Vector new_pos) {
	m_corner = new_pos;
}

df::Vector df::Box::getCorner() const {
	return m_corner;
}

void df::Box::setHorizontal(float new_horizontal) {
	m_horizontal = new_horizontal;
}

float df::Box::getHorizontal() const {
	return m_horizontal;
}

void df::Box::setVertical(float new_vertical) {
	m_vertical = new_vertical;
}

float df::Box::getVertical() const {
	return m_vertical;
}