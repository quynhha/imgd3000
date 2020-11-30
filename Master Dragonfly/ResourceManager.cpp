//Thi Quynh Ha Nguyen - Dragonfly Master
/*
ResourceManager.cpp
*/

#include "ResourceManager.h"
#include "LogManager.h"

#include <iostream>
#include <fstream>



// Read singleline ‘tag number’ ,return number ( e.g., ”frames 5”)
int readLineInt(std::ifstream *p_file, int *p_line_num, const char *tag);

// Read singleline ‘tag string’ ,return string ( e.g., ”color green”)
std::string readLineStr(std::ifstream *p_file, int *p_line_num, const char *tag);

// Read frame until 'eof' return Frame
df::Frame readFrame(std::ifstream *p_file, int *p_line_number, int width, int height);

df::ResourceManager::ResourceManager()
{
	setType("ResourceManager");

	//Sprite *p_sprite[MAX_SPRITES];
}

// Get the singleton instance of GameManager
df::ResourceManager& df::ResourceManager::getInstance()
{
	static df::ResourceManager instance;

	return instance;
}


int df::ResourceManager::startUp()
{
	
	m_sound_count = 0;
	m_music_count = 0;

	return Manager::startUp();
}

void df::ResourceManager::shutDown()
{
	Manager::shutDown();
}

std::string readLineStr(std::ifstream *p_file, int *p_line_number, const char *tag) {
	std::string line;

	if (!p_file->good()) {
		throw std::runtime_error("p_file marked as not good!");
	}

	try {
		std::getline(*p_file, line);
	}
	catch (std::exception e) {
		throw std::runtime_error("Failed getline from p_file!");
	}

	if (line.compare(0, strlen(tag), tag)) {
		throw std::runtime_error("tag not properly read from file!");
	}

	(*p_line_number)++;
	
	std::string output;
	if (line.length() == strlen(tag)) {
		output = "";
	}
	else {
		output = line.substr(strlen(tag) + 1);
	}

	return output;
}


df::Frame readFrame(std::ifstream *p_file, int *p_line_number, int width, int height) {
	std::string line, frame_str;

	if (!p_file->good()) {
		LM.writeLog("Error line %d. p_file no good!", *p_line_number);
		LM.writeLog("Defaulting to empty frame!");
		return df::Frame();
	}

	for (int i = 1; i <= height; i++) {
		try {
			std::getline(*p_file, line);
		}
		catch (std::exception e) {
			LM.writeLog("Error line %d. Failed getline from p_file!");
			LM.writeLog("Defaulting to empty frame!");
			return df::Frame();
		}
		(*p_line_number)++;

		if (line.length() != width) {
			LM.writeLog("Error line %d. Line width %d, expected %d.", *p_line_number, line.length(), width);
			LM.writeLog("Defaulting to empty frame!");
			return df::Frame();
		}

		frame_str += line;
		
	}

	if (!p_file->good()) {
		LM.writeLog("Error line %d. p_file no good!", *p_line_number);
		LM.writeLog("Defaulting to empty frame!");
		return df::Frame();
	}

	try {
		std::getline(*p_file, line);
	}
	catch (std::exception e) {
		LM.writeLog("Error line %d. Failed getline from p_file!");
		LM.writeLog("Defaulting to empty frame!");
		return df::Frame();
	}

	//if (line.compare(0, df::END_FRAME_TOKEN.length(), df::END_FRAME_TOKEN)) {
	if (line != END_FRAME_TOKEN) {
		LM.writeLog("Error line %d. Failed to find end of frame token!");
		LM.writeLog("Defaulting to empty frame!");
		return df::Frame();
	}

	df::Frame frame = df::Frame(width, height, frame_str);
	//LM.writeLog("Added Frame: \n%s", frame.getString().c_str());
	return frame;
}




int df::ResourceManager::loadSound(std::string filename, std::string label) {
	if (m_sound_count == MAX_SOUNDS) {
		LM.writeLog("Sound array full, failed to load sound!");
		return -1;
	}

	if (m_sound[m_sound_count].loadSound(filename) == -1) {
		LM.writeLog("Failed to load sound from file!");
		return -1;
	}

	m_sound[m_sound_count].setLabel(label);
	m_sound_count++;
	return 0;
}

int df::ResourceManager::unloadSound(std::string label) {
	for (int i = 0; i <= m_sound_count; i++) {
		if (label == m_sound[i].getLabel()) {
			for (int j = 0; j < m_sound_count - 2; j++) {
				m_sound[j] = m_sound[j + 1];
			}
			m_sound_count--;
			return 0;
		}
	}
	return -1;
}

df::Sound *df::ResourceManager::getSound(std::string label) {
	for (int i = 0; i <= m_sound_count; i++) {
		if (label == m_sound[i].getLabel())
			return(&m_sound[i]);
	}
	return NULL; //sound not found
}

int df::ResourceManager::loadMusic(std::string filename, std::string label) {
	if (m_music_count == MAX_MUSICS) {
		LM.writeLog("Music array full, failed to load music!");
		return -1;
	}

	if (m_music[m_music_count].loadMusic(filename) == -1) {
		LM.writeLog("Failed to load music from file!");
		return -1;
	}

	m_music[m_music_count].setLabel(label);
	m_music_count++;
	return 0;
}

int df::ResourceManager::unloadMusic(std::string label) {
	for (int i = 0; i <= m_music_count; i++) {
		if (label == m_music[i].getLabel()) {
			m_music[i].setLabel("");
			return 0;
		}
	}
	return -1;
}

df::Music *df::ResourceManager::getMusic(std::string label) {
	for (int i = 0; i < m_music_count; i++) {
		if (label == m_music[i].getLabel())
			return(&m_music[i]);
	}
	return NULL; // Music not found
}