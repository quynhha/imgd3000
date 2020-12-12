#include "EnemyMagicEvent.h"

EnemyMagicEvent::EnemyMagicEvent()
{
	setLocation(df::BOTTOM_CENTER);
	setViewString(ENEMY_MAGIC_BLOOD);
	setColor(df::BLUE);
	setValue(30);
}

EnemyMagicEvent::EnemyMagicEvent(int a)
{
	setLocation(df::BOTTOM_CENTER);
	setViewString(ENEMY_MAGIC_BLOOD);
	setColor(df::BLUE);
	setValue(a);
}
