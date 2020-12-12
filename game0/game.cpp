//
// game.cpp
// 

// Engine includes.
#include "ResourceManager.h"
#include "GameManager.h"
#include "LogManager.h"
#include "Saucer.h"
#include "Hero.h"
#include "Bullet.h"
#include "Points.h"
#include "Color.h"
#include "Star.h"
#include "GameStart.h"
#include "Pause.h"

// Function prototypes.
void loadResources(void);
void populateWorld(void);

int main(int argc, char *argv[]) {
  // Start up game manager.
    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 0;
    }

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  // Show splash screen.
  df::splash();

  // Load game resources.
  loadResources();
  

  // Populate game world with some objects.
  populateWorld();

  // Enable player to pause game.
  new df::Pause(df::Keyboard::F10);

  GM.run();

  // Shut everything down.
  GM.shutDown();
}
void loadResources(void) {
    // Load saucer sprite.
    RM.loadSprite("sprites/saucer-spr.txt", "saucer");
    // Load hero/ship sprite.
    RM.loadSprite("sprites/ship-spr.txt", "ship");
    // Load bullet sprite.
    RM.loadSprite("sprites/bullet-spr.txt", "bullet");
    // Load explosion sprite. 
    RM.loadSprite("sprites/explosion-spr.txt", "explosion");
    // Load gameover sprites
    RM.loadSprite("sprites/gameover-spr.txt", "gameover");
    //Load enemy
    RM.loadSprite("sprites/enemy-spr.txt", "enemy");
    // Load gamestart sprites
    RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
    RM.loadSound("sounds/fire.wav", "fire");
    RM.loadSound("sounds/explode.wav", "explode");
    RM.loadSound("sounds/nuke.wav", "nuke");
    RM.loadSound("sounds/game-over.wav", "game over");
    RM.loadMusic("sounds/start-music.wav", "start music");
    
}
void populateWorld(void) {

    // Create some Stars.
    for (int i = 0; i < 16; i++)
        new Star;
    // Spawn GameStart object.
    new GameStart();
    
}
