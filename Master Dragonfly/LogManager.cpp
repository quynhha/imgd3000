//Thi Quynh Ha Nguyen - Dragonfly Master
/*
LogManager.cpp
*/

#include "LogManager.h"
#include <stdarg.h>
#include <stdio.h>
#include "utility.h"

// Sets up the manager to basic requirments
df::LogManager::LogManager()
{
	setType("LogManager");
	p_f = NULL;
	do_flush = false;
}

// If the file is open close it
df::LogManager::~LogManager()
{
	if (p_f != NULL) {
		fclose(p_f);
		p_f = NULL;
	}
}

// Call parent method, and open the log file needed for write
#pragma warning (disable : 4996)
int df::LogManager::startUp()
{
	Manager::startUp();
	p_f = fopen(LOGFILE_NAME.c_str(), "w+");
	if (p_f == nullptr) {
		std::fprintf(stderr, "Cannot open logfile!\n");
		return -1;
	}
	writeLog("LogManager: LogManager successfully started\n");

	return 0;

}

// Call parent class method then close the file if its open
void df::LogManager::shutDown()
{
	Manager::shutDown();
	if (p_f != NULL) {
		fclose(p_f);
		p_f = NULL;
	}
}

// If the file has been open, write a message to it, making sure to go
// to the next line at the end of the messege
int df::LogManager::writeLog(const char *fmt, ...) const
{
	int success = 0;
	va_list args;
	va_start(args, fmt);
	success = vfprintf(p_f, fmt, args);
	va_end(args);
	if (do_flush && success >= 0) {
		success = fflush(p_f);
	}
	return success;
}

// Allows setting of flush bool
void df::LogManager::setFlush(bool do_flush)
{
	this->do_flush = do_flush;
}

// Sets up class a singleton and is used to get access of the Logmanager instance
df::LogManager& df::LogManager::getInstance()
{
	static df::LogManager instance;

	return instance;
}
