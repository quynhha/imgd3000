
//Thi Quynh Ha Nguyen - Dragonfly Master
/* 
utility.cpp
*/
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <sstream>

#include "utility.h"
#include "LogManager.h"
#include "WorldManager.h"

using std::stringstream;

/*
// Return a nicely-formatted time string HH:MM:SS
char *df::getTimeString()
{
	// String to return, made 'static' so persists
	static char time_str[30];

	// System calls to get Time
	time_t now;
	time(&now);
	struct tm *p_time = localtime(&now);

	// '02' gives two digits, '%d' for integers
	printf(time_str, "%02d:%02d:%02d",
		p_time->tm_hour,
		p_time->tm_min,
		p_time->tm_sec);

	return time_str;
}*/


bool df::posititonsIntersect(Vector p1, Vector p2) {
	if ((abs(p1.getX() - p2.getX()) <= 1) &&
		(abs(p1.getY() - p2.getY()) <= 1)) {
		return true;
	}
	else {
		return false;
	}
}


bool df::boxIntersectsBox(df::Box a, df::Box b) {
	float ax1 = a.getCorner().getX();
	float ax2 = a.getCorner().getX() + a.getHorizontal();
	float ay1 = a.getCorner().getY();
	float ay2 = a.getCorner().getY() + a.getVertical();
	float bx1 = b.getCorner().getX();
	float bx2 = b.getCorner().getX() + b.getHorizontal();
	float by1 = b.getCorner().getY();
	float by2 = b.getCorner().getY() + b.getVertical();

	auto x_overlap = (bx1 <= ax1 && ax1 <= bx2) ||
		(ax1 <= bx1 && bx1 <= ax2);
	auto y_overlap = (by1 <= ay1 && ay1 <= by2) ||
		(ay1 <= by1 && by1 <= ay2);
	return x_overlap && y_overlap;
}


df::Box df::getWorldBox(const Object *p_o) {
	Box temp_box = p_o->getBox();
	Vector corner = temp_box.getCorner();

	temp_box = getWorldBox(p_o, p_o->getPosition());

	return temp_box;
}

df::Box df::getWorldBox(const Object *p_o, Vector where) {
	Box temp_box = p_o->getBox();
	Vector corner = temp_box.getCorner();
	corner.setX(corner.getX() + where.getX());
	corner.setY(corner.getY() + where.getY());
	temp_box.setCorner(corner);

	return temp_box;

}


df::Vector df::worldToView(Vector world_pos) {
	Vector view_origin = WM.getView().getCorner();

	float view_x = view_origin.getX();
	float view_y = view_origin.getY();
	Vector view_pos(world_pos.getX() - view_x, world_pos.getY() - view_y);
	return view_pos;
}


df::Vector df::viewToWorld(Vector world_pos) {
	Vector view_origin = WM.getView().getCorner();

	float view_x = view_origin.getX();
	float view_y = view_origin.getY();
	Vector view_pos(world_pos.getX() + view_x, world_pos.getY() + view_y);

	return view_pos;
}


std::string df::toString(int i) {
	std::stringstream ss;	//create stringstream
	ss << i;;				//Add a number to stream.
	return ss.str();		//Return string with contents of stream
}