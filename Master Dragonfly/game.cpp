//
// game.cpp
// 

///The game should work 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
 
// Game includes.
#include "Hero.h"
#include "Star.h"
#include "Saucer.h"
#include "GameStart.h"

// Function prototypes.
void loadResources(void);
void populateWorld(void);
 
int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 0;
  }

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  loadResources();
  LM.writeLog("Loading Resources!!!\n");

  // Setup some objects.
  populateWorld();
 
  // Run game (this blocks until game loop is over).
  GM.run();
 
  // Shut everything down.
  GM.shutDown();
}
 
// Load resources (sprites, sound effects, music).
void loadResources(void) {
    RM.loadSprite("sprites/saucer-spr.txt", "saucer");
    RM.loadSprite("sprites/cat-spr.txt", "cat");
    RM.loadSprite("sprites/ship-spr.txt", "ship");
    RM.loadSprite("sprites/bullet-spr.txt", "bullet");
    RM.loadSprite("sprites/explosion-spr.txt", "explosion");
    RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
    RM.loadSprite("sprites/gameover-spr.txt", "gameover");
    RM.loadSound("sounds/fire.wav", "fire");
    RM.loadSound("sounds/explode.wav", "explode");
    RM.loadSound("sounds/nuke.wav", "nuke");
    RM.loadSound("sounds/game-over.wav", "game over");
    RM.loadMusic("sounds/start-music.wav", "start music");
}

// Populate world with some objects.
void populateWorld(void) {

  // Spawn some Stars.
  for (int i=0; i<30; i++) 
    new Star;
 

/*  // Create hero.
  new Hero;

  // Spawn some saucers to shoot.
  for (int i=0; i<16; i++)
    new Saucer;*/
    // Create GameStart object.
  new GameStart();
}
