
//Thi Quynh Ha Nguyen - Dragonfly Master
/* 
LogManager.h
*/

#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

// System includes
#include <stdio.h>

// Engine includes
#include "Manager.h"

// Two-letter acronym for easier access to manager
#define LM df::LogManager::getInstance()

namespace df {

	const std::string LOGFILE_NAME = "dragonfly.log";

	class LogManager : public Manager {

	private:
		LogManager();                       // Private due to Singleton
		LogManager(LogManager const&);      // Dont allow copies
		void operator=(LogManager const&);  // dont allow assignment
		bool do_flush;    // True if flush to disk after every write
		FILE *p_f;

	public:
		// If log file is open, close it
		~LogManager();

		// Get the one and only instance of LogManager
		static LogManager &getInstance();

		// Start log manager (open "dragonfly.log")
		int startUp();

		// Shutdown log manager (close "dragonfly.log")
		void shutDown();

		// Set flush of log file after each write
		void setFlush(bool do_flush = true);

		// write to logfile using printf() formatting of strings
		// return number of bytes written, -1 if error
		int writeLog(const char *fmt, ...) const;
	};

} // End namespace df
#endif // __LOG_MANAGER_H__