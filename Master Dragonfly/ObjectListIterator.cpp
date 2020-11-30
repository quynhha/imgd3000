//Thi Quynh Ha Nguyen - Dragonfly Master
/*
ObjectListIterator.cpp
*/

#include "Object.h"
#include "ObjectList.h"
#include "ObjectListIterator.h"

// Create iterator over indicated list
df::ObjectListIterator::ObjectListIterator(const ObjectList *p_l)
{
	index = 0;
	p_list = p_l;
}

// Set iterator to first item in list
void df::ObjectListIterator::first() {
	index = 0;
}

// Set iterator to next item in list
void df::ObjectListIterator::next() {
	if (index < p_list->count)
		index++;
}

// Return true if at end of list
bool df::ObjectListIterator::isDone() const {
	return (index == p_list->count);
}

// return pointer to current Object, NULL if done/empty
df::Object* df::ObjectListIterator::currentObject() const {
	return p_list->p_obj[index];
}