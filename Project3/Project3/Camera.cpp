//
// Camera.cpp
//

// Game includes.
#include "Camera.h"

// Engine includes.
#include "Box.h"
#include "DisplayManager.h"
#include "EventKeyboard.h"
#include "GameManager.h"
#include "LogManager.h"	
#include "WorldManager.h"
#include "GameStart.h"

Camera::Camera() {
  setType("Camera");
  setSolidness(df::SPECTRAL);
  // Start in middle of world.
  df::Box boundary = WM.getBoundary();
  setPosition(df::Vector(boundary.getHorizontal()/2, boundary.getVertical()/2));


  // Keyboard to control camera.
  registerInterest(df::KEYBOARD_EVENT);

  // View follows this object.
  new GameStart();
}

// Handle event.
int Camera::eventHandler(const df::Event *p_e) {
#ifdef DEBUG
  df::LogManager &log_manager = df::LogManager::getInstance();
  log_manager.writeLog("Camera::eventHandler(): Event type %s",
		       p_e->getType().c_str());
#endif
  float dx=0, dy=0;

  // Keyboard to move Camera around world.
  if (p_e->getType() == df::KEYBOARD_EVENT) {
    const df::EventKeyboard *p_ke = static_cast <const df::EventKeyboard *> (p_e);
#ifdef DEBUG
    log_manager.writeLog("\tKey is %d", p_ke->getKey());
#endif
    switch(p_ke->getKey()) {
    case df::Keyboard::UPARROW:	   // up arrow
      dy = -1 * CAMERA_SPEED;
      break;
    case df::Keyboard::DOWNARROW:  // down arrow
      dy = +1 * CAMERA_SPEED;
      break;
    case df::Keyboard::LEFTARROW:  // left arrow
      dx = -3 * CAMERA_SPEED;
      break;
    case df::Keyboard::RIGHTARROW: // right arrow
      dx = +3 * CAMERA_SPEED;
      break;
    case df::Keyboard::Q:     // q - quits
      GM.setGameOver(true);
      break;
    default:
      break;
    }

#ifdef DEBUG
    log_manager.writeLog("\tdx is %.2f, dy is %.2f", dx, dy);
#endif

    // Get new position.
    df::Vector new_pos(getPosition().getX() + dx, getPosition().getY() + dy);
#ifdef DEBUG
    df::LogManager &log_manager = df::LogManager::getInstance();
    log_manager.writeLog("Camera::eventHandler(): New position (%.2f,%.2f)",
			new_pos.getX(), new_pos.getY());
#endif

    // Keep screen (centered on Camera) within world boundaries.
    float screen_width = WM.getView().getHorizontal();
    float screen_height = WM.getView().getVertical();
    float world_width = WM.getBoundary().getHorizontal();
    float world_height = WM.getBoundary().getVertical();
    if ((new_pos.getY() - screen_height/2.0 > 0) && 
	(new_pos.getY() + screen_height/2.0 < world_height) &&
	(new_pos.getX() - screen_width/2.0 > 0) && 
	(new_pos.getX() - screen_width/2.0 < world_width))
      WM.moveObject(this, new_pos);
    return true;
  }

  return false;
}

// Draw "Instructions" on screen, along with box around border.
int Camera::draw() {
    //df::Object::draw();

  // Display instructions in center of screen.
  float max_x = WM.getView().getHorizontal();
  float max_y = WM.getView().getVertical();
  df::Vector pos = viewToWorld(df::Vector(max_x/2, max_y/2));
#ifdef DEBUG
  LM.writeLog("Camera::draw(): Drawing at (%.2f,%.2f)",
	      pos.getX(), pos.getY());

  DM.drawString(pos, "Press Arrow Keys to Move Camera, 'q' to Quit", 
		df::CENTER_JUSTIFIED, 
		df::WHITE);
#endif
  // Draw box around screen.
  for (int i=1; i < max_x; i++) {
    DM.drawCh(viewToWorld(df::Vector((float)i,0)), '-', df::RED);
    DM.drawCh(viewToWorld(df::Vector((float)i,max_y-1)), '-', df::RED);
  }
  for (int i=1; i < max_y; i++) {
    DM.drawCh(viewToWorld(df::Vector(0, (float)i)), '|', df::RED);
    DM.drawCh(viewToWorld(df::Vector(max_x-1, (float)i)), '|', df::RED);
  }

  return 1;
}

