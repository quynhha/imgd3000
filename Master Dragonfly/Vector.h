
//Thi Quynh Ha Nguyen - Dragonfly Master
/*
Vector.h
*/

#ifndef __VECTOR_H__
#define __VECTOR_H__

namespace df {

	class Vector {

	private:
		float x;  // Horizontal component
		float y;  // Vertical component

	public:
		// Create Vector with (x,y)
		Vector(float init_x, float init_y);

		// Default 2d (x,y) is (0,0)
		Vector();

		// Get/Set Horizontal component
		void setX(float new_x);
		float getX() const;

		// Get/Set Vertical component
		void setY(float new_y);
		float getY() const;

		// Set horrizontal and vertical components
		void setXY(float new_x, float new_y);

		// Return magnitude of vector
		float getMagnitude() const;

		// Normalize Vector
		void normalize();

		// Scale Vector
		void scale(float s);

		// Add two vectors, return new vector
		Vector operator+(const Vector &other) const;
	};

} // end of df namespace
#endif // __VECTOR_H__