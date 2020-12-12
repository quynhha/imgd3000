//
// Rock.cpp
// 
#include <stdlib.h>		// for random

// Engine includes.
#include "DisplayManager.h"
#include "WorldManager.h"

// Game includes.
#include "Rock.h"

#define ROCK_CHAR '.'
#define ROCK_COLOR df::YELLOW

Rock::Rock() {
  setType("Rock");
  setSolidness(df::SOFT);
  setAltitude(0);
  setPosition(df::Vector((rand()%(int)WM.getBoundary().getHorizontal()),
			 (rand()%(int)WM.getBoundary().getVertical())));
}

// Draw a "rock" on the screen.
int Rock::draw() {
  return DM.drawCh(getPosition(), ROCK_CHAR, ROCK_COLOR); 
}

