//Thi Quynh Ha Nguyen - Master Dragonfly
/*
DisplayManager.h
*/

#ifndef __DISPLAYMANAGER_H__
#define __DISPLAYMANAGER_H__
// System includes.
#include <SFML/Graphics.hpp>

// Engine includes.
#include "Color.h"
#include "Manager.h"
#include "Vector.h"
#include "Frame.h"

//Defaults for SFML window.
const int WINDOW_HORIZONTAL_PIXELS_DEFAULT = 1024;
const int WINDOW_VERTICAL_PIXELS_DEFAULT = 768;
const int WINDOW_HORIZONTAL_CHARS_DEFAULT = 120;
const int WINDOW_VERTICAL_CHARS_DEFAULT = 36;
const int WINDOW_STYLE_DEFAULT = sf::Style::Titlebar | sf::Style::Close;
const sf::Color WINDOW_BACKGROUND_COLOR_DEFAULT = sf::Color::Black;
const std::string WINDOW_TITLE_DEFAULT = "Dragonfly";
const std::string FONT_FILE_DEFAULT = "df-font.ttf";
const bool TEXT_OPAQUE_DEFAULT = true;


// Two-letter acronym for easier access to manager.
#define DM df::DisplayManager::getInstance()
namespace df {
	enum Justification
	{
		LEFT_JUSTIFIED,
		CENTER_JUSTIFIED,
		RIGHT_JUSTIFIED,
	};

	class DisplayManager : public Manager {

	private:
		sf::Color m_window_background_color;
		DisplayManager();
		DisplayManager(DisplayManager const&);
		void operator=(DisplayManager const&);
		sf::Font font;                // Font used for ASCII graphics.
		sf::RenderWindow* p_window;   // Pointer to SFML window.
		int window_horizontal_pixels; // Horizontal pixels in window.
		int window_vertical_pixels;   // Vertical pixels in window.
		int window_horizontal_chars;  // Horizontal ASCII spaces in window.
		int window_vertical_chars;    // Vertical ASCII spaces in window.
		int window_style;
		sf::Color window_background_color;
		std::string window_title;
		std::string font_file;
		bool opaque_text;

	public:
		static DisplayManager& getInstance();
		//~DisplayManager();
		// Open graphics window ready for text-based display.
		// Return 0 if ok, else -1.
		int startUp();

		// Close graphics window.
		void shutDown();

		// Draw a character at screen location (x,y) with color.
		// Return 0 if ok, else -1.
		int drawCh(Vector world_pos, char ch, Color color) const;

		// Return window's horizontal maximum (in characters).
		int getHorizontal() const;

		// Return window's vertical maximum (in characters).
		int getVertical() const;

		// Return window's horizontal maximum (in pixels).
		int getHorizontalPixels() const;

		// Return window's vertical maximum (in pixels).
		int getVerticalPixels() const;

		// Render current display buffer.
		// Return 0 if ok, else -1.
		int swapBuffers();

		// Return pointer to SFML drawing window.
		sf::RenderWindow* getWindow() const;

		// Draw string at windoe location (x,y) with dfault color.
		// Justified left, center or right. 
		// Return 0 if ok, else -1. 
		int drawString(Vector pos, std::string str, Justification just, Color color) const;

		// Set default background color. Return true if oke, else false. 
		bool setBackgroundColor(Color new_color);

		// Draw a single sprite frame at window locatio x,y
		int drawFrame(Vector world_pos, Frame frame, bool centered, Color color) const;

	};
	// Compute character height, based on window size and font.
	float charHeight();

	// Compute character width, based on window size and font.
	float charWidth();

	// Convert ASCII spaces (x,y) to window pixels (x,y).
	Vector spacesToPixels(Vector spaces);

	// Convert window pixels (x,y) to ASCII spaces (x,y).
	Vector pixelsToSpaces(Vector pixels);

}// end of namespace df
#endif // __DISPLAYMANAGER_H__
