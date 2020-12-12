#pragma once
#include "Event.h"
#include "ViewObject.h"

#define ENEMY_MAGIC_BLOOD "Enemy Magical HP"

class EnemyMagicEvent : public df::ViewObject {
public:
	EnemyMagicEvent();
	EnemyMagicEvent(int a);
};
