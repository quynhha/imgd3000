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
#include "WorldManager.h"
#include "Points.h"
#include "Color.h"
#include "Star.h"
#include "Rock.h"
#include "Camera.h"
#include "GameStart.h"
#include "Pause.h"
#include <DisplayManager.h>

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

  // Set world boundary twice as big as the screen with no view slack.
  df::Box boundary = WM.getBoundary();
  df::Vector corner(0, 0);
  df::Box new_boundary(corner,
      boundary.getHorizontal() * 3,
      boundary.getVertical());
  WM.setBoundary(new_boundary);
  WM.setViewSlack(df::Vector(0, 0));

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
    RM.loadSprite("sprites/ene-bullet.txt", "enebullet");

    RM.loadSprite("sprites/magic-spr.txt", "magic");

    RM.loadSprite("sprites/dog-spr-2.txt", "dog2");

    RM.loadSprite("sprites/cat-spr.txt", "cat");
    // Load explosion sprite. 
    RM.loadSprite("sprites/explosion-spr.txt", "explosion");
    // Load gameover sprites
    RM.loadSprite("sprites/gameover-spr.txt", "gameover");
    RM.loadSprite("sprites/win-spr.txt", "win");
    //Load enemy
    RM.loadSprite("sprites/enemy-spr.txt", "enemy");
    RM.loadSprite("sprites/food-spr.txt", "food");
    RM.loadSprite("sprites/door-spr.txt", "door");
    RM.loadSprite("sprites/grapes-spr.txt", "grape");
    RM.loadSprite("sprites/intotheFor-spr.txt", "forest");
    RM.loadSprite("sprites/test1.txt", "test1");
    RM.loadSprite("sprites/testenemy.txt", "testenemy");
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
    //for (int i = 0; i < 16; i++)
   //     new Star;
    // Spawn GameStart object.
    // Create some rocks for decoration.
    for (int i = 0; i < 100; i++)
        new Rock;


    // Draw box around screen.
    new GameStart(); 
    
}

