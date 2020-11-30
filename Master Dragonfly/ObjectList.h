//Thi Quynh Ha Nguyen - Dragonfly Master
/*
ObjectList.h
*/

#ifndef __OBJECT_LIST_H__
#define __OBJECT_LIST_H__

const int MAX_OBJECTS = 5000;

#include "Object.h"
#include "ObjectListIterator.h"

namespace df {

	class ObjectListIterator;

	class ObjectList {

	private:
		int count;                  // Count of objects in list
		Object *p_obj[MAX_OBJECTS]; // Array of pointers to objects

	public:
		friend class ObjectListIterator;

		// Default constructor
		ObjectList();

		// Insert object pointer in list
		// return 0 if ok, else -1
		int insert(Object *p_o);

		// Remove object pointer from list
		// return 0 if found, else -1
		int remove(Object *p_o);

		// clear list (setting count to 0)
		void clear();

		// Return count of number of objects in list
		int getCount() const;

		// return true if list is empty, else false
		bool isEmpty() const;

		// return true if list is Full, else false
		bool isFull() const;

	};

} // End df namespace
#endif // __OBJECT_LIST_H__