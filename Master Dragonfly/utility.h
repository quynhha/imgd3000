//Thi Quynh Ha Nguyen - Dragonfly Master
/*
utility.h
*/

#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "Vector.h"
#include "Box.h"
#include "Object.h"

namespace df {

	// Returns pretty-formatted time as char * string
	//char *getTimeString();

	// Return true if teo positions intersecct, else false
	bool posititonsIntersect(Vector p1, Vector p2);
	bool boxIntersectsBox(Box A, Box B);
	Box getWorldBox(const Object *p_o);
	Box getWorldBox(const Object *p_o, Vector where);

	Vector worldToView(Vector world_pos);
	Vector viewToWorld(Vector world_pos);

	std::string toString(int i);

} // End of df namespace
#endif // __UTILITY_H__