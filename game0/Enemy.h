/*
Enemy.h
*/

#include "EventCollision.h"
#include "Object.h"
#include "EventCollision.h"

class Enemy : public df::Object {
public:
	Enemy();
	~Enemy();
	int enemyhp;

private:
	void hit(const df::EventCollision* p_c);
	int eventHandler(const df::Event* p_e);
	void die();
	void moveToStart();
	void out();
};