//Thi Quynh Ha Nguyen - Master Dragonfly
/*
ReosurceManager.h
*/
#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

// System includes.
#include <SFML/Audio.hpp>
#include <string>

// Engine includes.
#include "Manager.h"
#include "Music.h"
#include "Sound.h"
#include "Sprite.h"
#include "SpriteResourceManager.h"

// Two-letter acronym for easier access to manager.
#define RM df::ResourceManager::getInstance()

namespace df {


	// Maximum number of unique assets in game.
	const int MAX_SOUNDS = 100;
	const int MAX_MUSICS = 50;

	class ResourceManager : public SpriteResourceManager {

	private:
		ResourceManager();                   // Private (a singleton).
		ResourceManager(ResourceManager const&); // Copy.
		void operator=(ResourceManager const&);   // Assignment.

		Sound m_sound[MAX_SOUNDS];	   ///< Array of sound buffers.
		int m_sound_count;	           ///< Count of number of loaded sounds.
		Music m_music[MAX_MUSICS];	   ///< Array of music buffers.
		int m_music_count;

	public:
		// Get the one and only instance of the ResourceManager.
		static ResourceManager& getInstance();

		// Get manager ready for resources.
		int startUp();

		// Shut down manager, freeing up any allocated Sprites.
		void shutDown();

		/// Load sound from file.
		/// Return 0 if ok, else -1.
		int loadSound(std::string filename, std::string label);

		/// Remove Sound with indicated label.
		/// Return 0 if ok, else -1.
		int unloadSound(std::string label);

		/// Find Sound with indicated label.
		/// Return pointer to it if found, else NULL.
		Sound* getSound(std::string label);

		/// Associate file with Music.
		/// Return 0 if ok, else -1.
		int loadMusic(std::string filename, std::string label);

		/// Remove label for Music with indicated label.
		/// Return 0 if ok, else -1.
		int unloadMusic(std::string label);

		/// Find Music with indicated label.
		/// Return pointer to it if found, else NULL.
		Music* getMusic(std::string label);
	};

} // end of namespace df
#endif //__RESOURCE_MANAGER_H__
