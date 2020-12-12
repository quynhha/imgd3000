/*
EnemyBlood.h
*/
#include "Event.h"
#include "ViewObject.h"

#define ENEMY_BLOOD "Enemy HP"

class EnemyBlood : public df::ViewObject{
public:
	EnemyBlood ();
	EnemyBlood(int a);
};
