
//Thi Quynh Ha Nguyen - Dragonfly Master
/*
Colors.h
*/

#ifndef __COLOR_H__
#define __COLOR_H__

namespace df {

	enum Color {
		UNDEFINED_COLOR = -1,
		BLACK = 0,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
		CUSTOM,
	};

	const Color COLOR_DEFAULT = WHITE;
}
// End df namespace
#endif // __COLOR_H__