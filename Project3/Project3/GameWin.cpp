#include "GameWin.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "EventView.h"
#include "EventOut.h"
#include "EventStep.h"
#include "GameStart.h"

void GameWin::step()
{
	time_to_live--;
	if (time_to_live <= 0)
		WM.markForDelete(this);
}

GameWin::GameWin()
{
    setType("GameWin");

	if (setSprite("win") == 0)
		time_to_live = getAnimation().getSprite()->getFrameCount() * getAnimation().getSprite()->getSlowdown();
	else
		time_to_live = 0;

    // Put in center of window.
    setLocation(df::CENTER_CENTER);

    // Register for step event.
    registerInterest(df::STEP_EVENT);
}

GameWin::~GameWin()
{
	df::ObjectList object_list = WM.getAllObjects(true);
	df::ObjectListIterator i(&object_list);
	for (i.first(); !i.isDone(); i.next()) {
		df::Object* p_o = i.currentObject();
		if (p_o->getType() == "Saucer" || p_o->getType() == "ViewObject")
			WM.markForDelete(p_o);
		if (p_o->getType() == "GameStart") {
			p_o->setActive(true);
			dynamic_cast <GameStart*> (p_o)->playMusic(); // Resume start music.
		}
	}
}

int GameWin::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::STEP_EVENT)
	{
		step();
		return 1;
	}

	return 0;
}

int GameWin::draw()
{
    return df::Object::draw();
}
