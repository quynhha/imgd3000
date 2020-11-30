
//Thi Quynh Ha Nguyen - Master Dragonfly
/*
DisplayManager.cpp
*/

#include "DisplayManager.h"
#include "LogManager.h"
#include "Color.h"
#include "utility.h"


// Set default fields
df::DisplayManager::DisplayManager()
{
	setType("DisplayManager");
	window_horizontal_pixels = WINDOW_HORIZONTAL_PIXELS_DEFAULT;
	window_vertical_pixels = WINDOW_VERTICAL_PIXELS_DEFAULT;
	window_horizontal_chars = WINDOW_HORIZONTAL_CHARS_DEFAULT;
	window_vertical_chars = WINDOW_VERTICAL_CHARS_DEFAULT;
	window_title = WINDOW_TITLE_DEFAULT;
	window_style = WINDOW_STYLE_DEFAULT;
	window_background_color = WINDOW_BACKGROUND_COLOR_DEFAULT;
	font_file = FONT_FILE_DEFAULT;
	opaque_text = TEXT_OPAQUE_DEFAULT;

}

// Get the singleton instance of GameManager
df::DisplayManager& df::DisplayManager::getInstance()
{
	static df::DisplayManager instance;

	return instance;
}

int df::DisplayManager::startUp() {
	if (p_window != nullptr)
	{
		return 0;
	}
	sf::VideoMode video_mode = sf::VideoMode(window_horizontal_pixels, window_vertical_pixels);
	p_window = new sf::RenderWindow(video_mode, window_title, window_style);

	if (p_window == nullptr) {
		LM.writeLog("DisplayManager: Failed to make SFML window\n");
		return -1;
	}
	//Turn off mouse cursor
	p_window->setMouseCursorVisible(false);

	// Synchronize refressh rate with monitor 
	p_window->setVerticalSyncEnabled(true);

	//Load font

	if (!font.loadFromFile(font_file)) {
		LM.writeLog("Failed to load font!!!");
		return -1;
	}


	Manager::startUp();
	LM.writeLog("DisplayManager: Display manager succesfully started\n");
	return 0;
}

void df::DisplayManager::shutDown() {
	p_window->close();
	delete p_window;
	df::Manager::shutDown();
}

int df::DisplayManager::drawCh(Vector world_pos, char ch, Color color) const {
	Vector view_pos = worldToView(world_pos);
	//Make sure window is allocated.
	if (p_window == NULL)
	{
		LM.writeLog("DisplayManager: Failed to drawCh(pos(%f, %f), %c): null window? %s, null font? %s\n",
			world_pos.getX(), world_pos.getY(), ch,
			p_window == nullptr ? "true" : "false");
		return -1;
	}

	// Convert spaces (x,y) to pixels (x,y)
	Vector pixel_pos = spacesToPixels(world_pos);

	// Draw background rectangle since text is "see through" in SFML
	if (opaque_text) {
		static sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(charWidth(), charHeight()));
		rectangle.setFillColor(window_background_color);
		rectangle.setPosition(pixel_pos.getX() - charWidth() / 10, pixel_pos.getY() + charHeight() / 5);
		p_window->draw(rectangle);
	}
	//Create character text to draw. 
	static sf::Text text("", font);
	text.setString(ch);
	text.setStyle(sf::Text::Bold);

	// Scale to right size. 
	if (charWidth() < charHeight())
	{
		text.setCharacterSize(charWidth() * 2);
	}
	else text.setCharacterSize(charHeight() * 2);

	switch (color)
	{
	case BLACK:
		text.setFillColor(sf::Color::Black);
		break;
	case RED:
		text.setFillColor(sf::Color::Red);
		break;
	case GREEN:
		text.setFillColor(sf::Color::Green);
		break;
	case YELLOW:
		text.setFillColor(sf::Color::Yellow);
		break;
	case BLUE:
		text.setFillColor(sf::Color::Blue);
		break;
	case MAGENTA:
		text.setFillColor(sf::Color::Magenta);
		break;
	case CYAN:
		text.setFillColor(sf::Color::Cyan);
		break;
	case WHITE:
		text.setFillColor(sf::Color::White);
		break;
	default:
		text.setFillColor(sf::Color::White);
		break;
	}

	// Set position in window (in pixels)
	text.setPosition(pixel_pos.getX(), pixel_pos.getY());

	//Draw character. 
	p_window->draw(text);

	return 0;
}

// Render current window buffer
// Return 0 if ok else -1
int df::DisplayManager::swapBuffers() {
	// Make sure window is allocated. 
	if (p_window == NULL)
	{
		return -1;
	}
	// Diaplay current window. 
	p_window->display();

	//Clear other window to get ready for next draw. 
	p_window->clear();

	return 0; // Success
}

float df::charHeight(void) {
	// DisplayManager getVerticalPixels()) divided by the number 
	// of vertical characters(DisplayManager getVertical()
	return (DM.getVerticalPixels() / DM.getVertical());
}

float df::charWidth(void) {
	// (DisplayManager getHorizontalPixels()) divided by the number of
	// horizontal characters(DisplayManager getHorizontal()
	return (DM.getHorizontalPixels() / DM.getHorizontal());
}

int df::DisplayManager::getVerticalPixels() const {
	return window_vertical_pixels;
}

int df::DisplayManager::getHorizontalPixels() const {
	return window_horizontal_pixels;
}


df::Vector df::spacesToPixels(Vector spaces) {
	Vector pixelVector;

	pixelVector.setX(spaces.getX() * charWidth());
	pixelVector.setY(spaces.getY() * charHeight());

	return pixelVector;
}

df::Vector df::pixelsToSpaces(Vector pixels) {
	Vector spacesVector;

	spacesVector.setX(pixels.getX() / charWidth());
	spacesVector.setY(pixels.getY() / charHeight());

	return spacesVector;
}

int df::DisplayManager::getHorizontal() const {
	return window_horizontal_chars;
}

int df::DisplayManager::getVertical() const {
	return window_vertical_chars;
}

// Draw string at window location (x,y) with color
// Justified left center or right
// return 0 if ok -1 otherwise
int df::DisplayManager::drawString(Vector pos, std::string str, Justification just, Color color) const {
	// Get starting position
	Vector starting_pos = pos;
	switch (just)
	{
	case df::LEFT_JUSTIFIED:
		break;
	case df::CENTER_JUSTIFIED:
		starting_pos.setX(pos.getX() - str.size() / 2);
		break;
	case df::RIGHT_JUSTIFIED:
		starting_pos.setX(pos.getX() - str.size());
		break;
	default:
		break;
	}

	// Draw string character by character
	for (int i = 0; i < str.size(); i++) {
		Vector temp_pos(starting_pos.getX() + i, starting_pos.getY());
		drawCh(temp_pos, str[i], color);
	}

	return 0;
}



int df::DisplayManager::drawFrame(Vector world_pos, Frame frame, bool centered, Color color) const {
	int x_off;
	int y_off;
	
	//LM.writeLog("Frame: %s", frame.getString().c_str());

	if (frame.getString().empty()) {
		LM.writeLog("Frame is empty");
		return -1;
	}

	// Center if true otherwise 0 out
	if (centered == true) {
		x_off = frame.getWidth() / 2;
		y_off = frame.getHeight() / 2;
	}
	else {
		x_off = 0;
		y_off = 0;
	}

	
	std::string str = frame.getString();

	// Draw frame, one character at a time
	for (int y = 0; y <= frame.getHeight() - 1; y++) {
		for (int x = 0; x <= frame.getWidth() - 1; x++) {
			Vector temp_pos(world_pos.getX() - x_off + x, world_pos.getY() - y_off + y);
			drawCh(temp_pos, str[y * frame.getWidth() + x], color);
		}
	}
	return 0;
}


bool df::DisplayManager::setBackgroundColor(Color new_color) {
	// Set SFML color based on Dragonfly color
	switch (new_color) {
	case UNDEFINED_COLOR:
		m_window_background_color = sf::Color::Transparent;
		break;
	case BLACK:
		m_window_background_color = sf::Color::Black;
		break;
	case RED:
		m_window_background_color = sf::Color::Red;
		break;
	case GREEN:
		m_window_background_color = sf::Color::Green;
		break;
	case YELLOW:
		m_window_background_color = sf::Color::Yellow;
		break;
	case BLUE:
		m_window_background_color = sf::Color::Blue;;
		break;
	case MAGENTA:
		m_window_background_color = sf::Color::Magenta;
		break;
	case CYAN:
		m_window_background_color = sf::Color::Cyan;
		break;
	case WHITE:
		m_window_background_color = sf::Color::White;
		break;
	case CUSTOM:
		m_window_background_color = sf::Color::Transparent;
		break;
	}

	return true;
}


sf::RenderWindow *df::DisplayManager::getWindow() const {
	return p_window;
}