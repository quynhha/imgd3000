//Thi Quynh Ha Nguyen - Dragonfly Master
/*
Music.cpp
*/
#include "Music.h"
#include "LogManager.h"

df::Music::Music() {

}

int df::Music::loadMusic(std::string filename) {
	if (m_music.openFromFile(filename)) {
		return 0;
	}
	LM.writeLog("Failed to open music file");
	return -1;
}

void df::Music::setLabel(std::string new_label) {
	m_label = new_label;
}

std::string df::Music::getLabel() const {
	return m_label;
}

void df::Music::play(bool loop) {
	m_music.play();
	m_music.setLoop(loop);
}

void df::Music::stop() {
	m_music.stop();
}

void df::Music::pause() {
	m_music.pause();
}

sf::Music *df::Music::getMusic() {
	return &m_music;
}