
//Thi Quynh Ha Nguyen - Dragonfly Master
/*
GameManager.cpp
*/

#include "GameManager.h"
#include "LogManager.h"
#include "Clock.h"
#include "WorldManager.h"
#include "ObjectList.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "ResourceManager.h"

#include <Windows.h>

// Set default fields
df::GameManager::GameManager()
{
	setType("GameManager");
	game_over = true;
	frame_time = FRAME_TIME_DEFAULT;
}

// Get the singleton instance of GameManager
df::GameManager& df::GameManager::getInstance()
{
	static df::GameManager instance;

	return instance;
}

// Set game over status to indicated value
// if true (default), will stop game loop
void df::GameManager::setGameOver(bool new_game_over)
{
	game_over = true;
}

// Get game over status
bool df::GameManager::getGameOver() const
{
	return game_over;
}

// Return frame time
// Frame time is target time for game loop, in milliseconds
int df::GameManager::getFrameTime() const
{
	return frame_time;
}

// Starts up all other managers in proper order
int df::GameManager::startUp()
{
	// Default Manager start up
	df::Manager::startUp();

	// Start Log Manager
	if (LM.startUp() != 0) {
		printf("### FAILED TO START LOG MANAGER ###\n");
		return 1;
	}
	else {
		LM.writeLog("### Log Manager Started Up ###\n");
	}
	
	// Start World Manager
	if (WM.startUp() != 0) {
		LM.writeLog("### FAILED TO START WORLD MANAGER ###\n");
		return 1;
	}
	else {
		LM.writeLog("### World Manager Started Up ###\n");
	}

	// Start Display Manager
	if (DM.startUp() != 0) {
		LM.writeLog("### FAILED TO START DISPLAY MANAGER ###\n");
		return 1;
	}
	else {
		LM.writeLog("### Display Manager Started Up ###\n");
	}

	// Start Input Manager
	if (IM.startUp() != 0) {
		LM.writeLog("### FAILED TO START INPUT MANAGER ###\n");
		return 1;
	}
	else {
		LM.writeLog("### Input Manager Started Up ###\n");
	}

	// Start Resource Manager
	if (RM.startUp() != 0) {
		LM.writeLog("### FAILED TO START RESOURCE MANAGER ###\n");
		return 1;
	}
	else {
		LM.writeLog("### Resource Manager Started Up ###\n");
	}

	WM.setBoundary(Box(Vector(0, 0), DM.getHorizontal(), DM.getVertical()));
	WM.setView(Box(Vector(0, 0), DM.getHorizontal(), DM.getVertical()));



	game_over = false;
	frame_time = 33;

	return 0;
}

// Shutdown all GameManager services
void df::GameManager::shutDown()
{
	df::Manager::shutDown();

	DM.shutDown();

	df::LogManager& log_manager = df::LogManager::getInstance();
	log_manager.writeLog("### Log Manager Shutting Down ###");
	log_manager.shutDown();

	game_over = true;
}

// The game loop
void df::GameManager::run()
{
	LM.writeLog("Game loop start");
	Clock clock;
	ObjectList world_objects;
	while (!game_over)
	{
		clock.delta();
		// ----- Get input -----
		IM.getInput();

		// ------ Step Event -----
		EventStep s(m_step_count);
		onEvent(&s);

		// ----- Update Game world state -----
		// Have objects update themselves
		WM.update();

		// Move all objects
		// Draw all objects
		WM.draw();
		
		// ----- Draw current scene to back buffer -----
		// ----- Swap back buffer to current buffer -----
		DM.swapBuffers();
		// ----- Sleep if needed -----
		int sleep_time = (getFrameTime() - clock.split()/1000);
		if (sleep_time > 0) {
			Sleep(sleep_time);
		}

		m_step_count++;
		// Record messege of game loop to the log
		//LM.writeLog("Full game loop processed");
	}
}