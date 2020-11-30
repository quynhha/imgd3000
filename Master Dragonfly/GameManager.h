//Thi Quynh Ha Nguyen - Dragonfly Master
/*
GameManager.h
*/

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "Manager.h"

// Two-letter acronym for easier access to manager
#define GM df::GameManager::getInstance()

namespace df {

	// Default frame time (game loop time) in millisecs (33 ms == 30 f/s)
	const int FRAME_TIME_DEFAULT = 33;

	class GameManager : public Manager {

	private:
		GameManager();                        // Private because singleton
		GameManager(GameManager const&);     // Dont allow copy
		void operator=(GameManager const&);   // Dont allow assignment
		bool game_over;   // True, then game loop should stop
		int frame_time;   // Target time per game loop, in milliseconds
		int m_step_count;

	public:
		// Get the singleton instance of GameManager
		static GameManager &getInstance();

		// Startup all GameManager services
		int startUp();

		// Shutdown all GameManager services
		void shutDown();

		// Run the game loop
		void run();

		// Set game over status to indicated value
		// if true (default), will stop game loop
		void setGameOver(bool new_game_over = true);

		// Get game over status
		bool getGameOver() const;

		// Return frame time
		// Frame time is target time for game loop, in milliseconds
		int getFrameTime() const;


	};

} // End df namespace
#endif // __GAME_MANAGER_H__