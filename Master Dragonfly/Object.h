
//Thi Quynh Ha Nguyen - Dragonfly Master
/*
Object.h
*/

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <string>

#include "Vector.h"
#include "Event.h"
#include "Sprite.h"
#include "Box.h"

namespace df {

	// Types of solidness of Object
	enum Solidness {
		HARD,       // Object causes collisions and impedes
		SOFT,       // Object causes collision, but doesn't impede
		SPECTRAL,   // Object doesn't cause collisions
	};

	class Object {


	private:
		int id;             // Unique object identifier
		std::string m_type;   // user-defined identifier
		Vector position;    // position in game world
		int m_altitude;

		Vector direction;	// Direction vector
		float speed;	// Object speed in direction

		Solidness m_solidness; // Solidness of object

		//attributes for sprites
		Sprite *p_sprite;
		bool sprite_centered; //When true, sprite is cented on object position
		int sprite_index;
		int sprite_slowdown; //Slowdown rate(1= no slowdown, - = stop)
		int sprite_slowdown_counter; //Slowdown counter

		Box box; // Box for sprite boundary and collisions

	public:
		// Construct object. Set default params and
		// add to game world (WorldManager)
		Object();

		// Destroy object
		// remove from game world (WorldManager)
		virtual ~Object();

		// set Object id
		void setId(int new_id);

		// get object id
		int getId() const;

		// set type identifier of object
		void setType(std::string new_type);

		// Get type identifier of object
		std::string getType() const;

		// set position of object
		void setPosition(Vector new_pos);

		// get position of object
		Vector getPosition() const;

		// Handle event by default ignoring everything
		// return 0 if ignored
		virtual int eventHandler(const Event *p_e);

		virtual void draw();

		// Set altitutde of Object with checks for range 0 - Max Alt
		// Return 0 if ok and -1 otherwise
		int setAltitude(int new_altitude);

		// Return altitude of object
		int getAltitude() const;

		// Set speed of Object
		void setSpeed(float speed);

		// Get speed pf Object
		float getSpeed() const;

		// Set direction of Object
		void setDirection(Vector newDirection);

		// Get direction of Object
		Vector getDirection() const;

		// Set direction and speed of Object
		void setVelocity(Vector new_Velocity);

		// Get velocity of Object based on the directiona and speed
		Vector getVelocity() const;

		// predict object position based on speed and direction
		// return predicted position
		Vector predictPosition();

		bool isSolid() const; // True if HARD or SOFT else false

		// Set object solidness with checks for consistency
		// Return 0 if okay and -1 if not
		int setSolidness(Solidness new_solid);

		// Return object solidness
		Solidness getSolidness() const;

		//methods associated with object's having sprite
		//Set object sprite to new one
		//If set_box is true, set bounding box to size of sprite
		//Set sprite index to 0 (first frame)
		void setSprite(Sprite *p_new_sprite, bool set_box = true);

		//return pointer to sprite associated with object
		Sprite *getSprite() const;

		//Set sprite to be centered at Object Position
		void setCentered(bool centered);
		//Check is sprite is centered
		bool isCentered() const;

		//Set index of current sprite sprite frame to be displayed
		void setSpriteIndex(int new_sprite_index);

		//Return index of current sprite frame to be displayed
		int getSpriteIndex() const;

		//Slow down sprite animations
		//Sprite slowdown is in multiples of GameManger frame time.
		void setSpriteSlowdown(int new_sprite_slowdown);
		int getSpriteSlowdown() const;
		void setSpriteSlowdownCounter(int new_sprite_slowdown_count);
		int getSpriteSlowdownCounter() const;

		// Set object's bounding box
		void setBox(Box new_box);
		// Get Object's bounding box
		Box getBox() const;
	};

} // end namespace df
#endif // __OBJECT_H__