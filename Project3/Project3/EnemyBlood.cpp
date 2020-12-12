/*
EnemyBlood.cpp
*/
#include "LogManager.h"
#include "EnemyBlood.h"
#include "Event.h"
#include "EventStep.h"
#include "LogManager.h"

EnemyBlood::EnemyBlood() {
	setLocation(df::BOTTOM_RIGHT);
	setViewString(ENEMY_BLOOD);
	setColor(df::BLUE);
	setValue(20);
}

EnemyBlood::EnemyBlood(int a)
{
	setLocation(df::BOTTOM_RIGHT);
	setViewString(ENEMY_BLOOD);
	setColor(df::BLUE);
	setValue(a);
}
