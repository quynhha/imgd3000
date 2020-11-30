//Thi Quynh Ha Nguyen - Dragonfly Master
/*
Frame.cpp
*/

#include "Frame.h"
#include "DisplayManager.h"

df::Frame::Frame() {
	m_width = 0;
	m_height = 0;
	m_frame_str = "";
}

df::Frame::Frame(int new_width, int new_height, std::string frame_str) {
	m_width = new_width;
	m_height = new_height;
	m_frame_str = frame_str;
}

void df::Frame::setWidth(int new_width) {
	m_width = new_width;
}

int df::Frame::getWidth() const {
	return m_width;
}

void df::Frame::setHeight(int new_height) {
	m_height = new_height;
}

int df::Frame::getHeight() const {
	return m_height;
}

void df::Frame::setString(std::string new_frame_string) {
	m_frame_str = new_frame_string;
}

std::string df::Frame::getString() const {
	return m_frame_str;
}
int df::Frame::draw(Vector position, Color color, char transparency) const
{
	if (m_frame_str.empty())
	{
		return -1;
	}

	int x_offset = getWidth() / 2;
	int y_offset = getHeight() / 2;

	for (int y = 0; y < m_height; y++)
	{
		for (int x = 0; x < m_width; x++) {
			Vector temp_pos(position.getX() + x - x_offset, position.getY() + y - y_offset);
			if (transparency == 0 || (m_frame_str[y * getWidth() + x] != transparency))
			{
				DM.drawCh(temp_pos, m_frame_str[y * m_width + x], color);
			}

		}
	}
	return 0;
}