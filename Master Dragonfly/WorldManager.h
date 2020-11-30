
//Thi Quynh Ha Nguyen - Dragonfly Master
/*
WorldManager.h
*/

#ifndef __WORLD_MANAGER_H__
#define __WORLD_MANAGER_H__

#include "Manager.h"
#include "ObjectList.h"

// Two-letter acronym for easier access to manager.
#define WM df::WorldManager::getInstance()


namespace df {

	const int MAX_ALTITUDE = 4;

	class WorldManager : Manager {


	private:
		WorldManager(); // singleton
		WorldManager(WorldManager const&); // Don't allow copy
		void operator=(WorldManager const&); // sont allow assignment
		

		ObjectList m_updates;  // All objects in the world to update
		ObjectList m_deletions; // All objects to be deleted

		Box boundary;   //World Boundary
		Box view;       //Player view of game world

		Object *p_view_following; //Object view is following

	public:
		// Get a signle instance
		static WorldManager &getInstance();

		// Startup game world by initializing everything
		int startUp();

		// Shutdown everything delete it all
		void shutDown();

		// inset objects into the world. return 0 if successful
		int insertObject(Object *p_o);

		// remove object from world return 0 if successful
		int removeObject(Object *p_o);

		// return list of all Objects in world
		ObjectList getAllObjects(bool inactive = false) const;

		// return list of all Objexts in world matching type
		ObjectList objectsOfType(std::string type) const;

		//update world
		// Delete objects marked for deletion
		void update();

		// Indicate Object is to be deleted at end of current game loop
		// return 0 if successful
		int markForDelete(Object *p_o);

		void draw(); // Call draw method on all objects in the world

		// Return list of Objects colllises with at position 'where'
		// Collisions only solid objects
		// Does not consider if p_o is solid or not
		ObjectList isCollision(Object *p_o, Vector where) const;

		// Move Object
		// If collidion with solid send collision events
		// if no collision eith solid move ok, else dont move object
		// if object is Spectral, move ok
		// Return 0 if moved okay, else -1 if collided with a solid
		int moveObject(Object *p_o, Vector where);

		// Send event to all Objects
		// Return count of number  of events sent
		int onEvent(const Event *p_event) const;

		//Set game world boundary
		void setBoundary(Box new_boundary);

		//Get game world boundary
		Box getBoundary() const;

		//Set player view of game world.
		void setView(Box new_view);

		//Get player view
		Box getView() const;

		//Set view to center window on Position view_pos
		//View edge will not go beyond world boundary
		void setViewPosition(Vector view_pos);

		//Set view to center window on Object
		//Set to NULL to stop following
		int setViewFollowing(Object *p_new_view_following);
	};

} // End df namespace
#endif // __WORLD_MANAGER_H__