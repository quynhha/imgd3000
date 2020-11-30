//Thi Quynh Ha Nguyen - Dragonfly Master
/*
Clock.cpp
*/

#include "Clock.h"

#include <Windows.h>

// Sets previous_time to current time
df::Clock::Clock()
{
	SYSTEMTIME temp_time;
	GetSystemTime(&temp_time);

	previous_time = (temp_time.wMinute * 60 * 1000000)
		+ (temp_time.wSecond * 1000000)
		+ (temp_time.wMilliseconds * 1000);
}

// Return time elapsed since delta() was last called, -1 if error
// Units are microseconds
long int df::Clock::delta()
{
	SYSTEMTIME temp_time;
	GetSystemTime(&temp_time);

	long int curr_time = (temp_time.wMinute * 60 * 1000000)
					   + (temp_time.wSecond * 1000000)
					   + (temp_time.wMilliseconds * 1000);

	long int elapsed_time = curr_time - previous_time;

	previous_time = curr_time;
	return elapsed_time;
}

// Return time elapsed since delta() was called, -1 if error
// Units are microseconds
long int df::Clock::split() const
{
	SYSTEMTIME temp_time;
	GetSystemTime(&temp_time);

	long int curr_time = (temp_time.wMinute * 60 * 1000000)
		+ (temp_time.wSecond * 1000000)
		+ (temp_time.wMilliseconds * 1000);

	long int elapsed_time = curr_time - previous_time;

	return elapsed_time;
}