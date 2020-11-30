
//Thi Quynh Ha Nguyen - Dragonfly Master
/*
Vector.cpp
*/

#include <math.h>

#include "Vector.h"

// Create Vector with (x,y)
df::Vector::Vector(float init_x, float init_y)
{
	x = init_x;
	y = init_y;
}

// Default 2d (x,y) is (0,0)
df::Vector::Vector()
{
	x = 0;
	y = 0;
}

// Set Horizontal component
void df::Vector::setX(float new_x) {
	x = new_x;
}

// Get Horizontal component
float df::Vector::getX() const {
	return x;
}

// Set Vertical component
void df::Vector::setY(float new_y) {
	y = new_y;
}

// Get Vertical component
float df::Vector::getY() const {
	return y;
}

// Set horrizontal and vertical components
void df::Vector::setXY(float new_x, float new_y) {
	x = new_x;
	y = new_y;
}

// Return magnitude of vector
float df::Vector::getMagnitude() const {
	return (float)(sqrt((x*x) + (y*y)));
}

// Normalize Vector
void df::Vector::normalize()
{
	float length = getMagnitude();
	if (length > 0) {
		x = x / length;
		y = y / length;
	}
}

// Scale Vector
void df::Vector::scale(float s)
{
	x = x * s;
	y = y * s;
}

// Add two vectors, return new vector
df::Vector df::Vector::operator+(const Vector &other) const
{
	Vector v;           // Create a new vector
	v.x = x + other.x;  // Add x components
	v.y = y + other.y;  // Add y component
	return v;           // return new vector
}