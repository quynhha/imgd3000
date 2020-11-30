
//Thi Quynh Ha Nguyen - Dragonfly Master
/*
ViewObject.h
*/

#include "ViewObject.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "utility.h"
#include "EventView.h"


df::ViewObject::ViewObject() {
	//Initialize object attributes
	setSolidness(SPECTRAL);
	setAltitude(MAX_ALTITUDE);
	setType("ViewObject");

	//Initialize viewobject attributes
	setValue(0);
	setLocation(TOP_CENTER);
	setColor(COLOR_DEFAULT);

	setDrawValue();
	setBorder(true);

	//Register interests
	//registerInterest(VIEW_EVENT); // if section 4.15 implemented
}


void df::ViewObject::setLocation(ViewObjectLocation new_location) {

	Vector p;
	int y_delta = 0;

	//set the new position based on location
	switch (new_location) {
	case TOP_LEFT:
		p.setXY(WM.getView().getHorizontal() * 1 / 6, 1);
		if (!getBorder())
			y_delta = -1;
		break;
	case TOP_CENTER:
		p.setXY(WM.getView().getHorizontal() * 3 / 6, 1);
		if (!getBorder())
			y_delta = -1;
		break;
	case TOP_RIGHT:
		p.setXY(WM.getView().getHorizontal() * 5 / 6, 1);
		if (!getBorder())
			y_delta = -1;
		break;
	case CENTER_CENTER:
		p.setXY(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() / 2);
		break;
	case BOTTOM_LEFT:
		p.setXY(WM.getView().getHorizontal() * 1 / 6, WM.getView().getVertical() - 2);
		if (!getBorder())
			y_delta = +1;
		break;
	case BOTTOM_CENTER:
		p.setXY(WM.getView().getHorizontal() * 3 / 6, WM.getView().getVertical() - 2);
		if (!getBorder())
			y_delta = +1;
		break;
	case BOTTOM_RIGHT:
		p.setXY(WM.getView().getHorizontal() * 5 / 6, WM.getView().getVertical() - 2);
		if (!getBorder())
			y_delta = +1;
		break;
	}

	// Shift as needed based on border
	p.setY(p.getY() + y_delta);

	// set position of Object
	setPosition(p);

	// Set new location
	m_location = new_location;
	
}

void df::ViewObject::setBorder(bool new_border) {
	if (m_border != new_border) {
		m_border = new_border;
		// Reset Location to account for border settings
		setLocation(getLocation());
	}
}

void df::ViewObject::draw() {
	std::string temp_str = "";
	std::string border_box = "";

	//Display view_string + value
	if (m_border) {
		border_box = "----";
		for (int i = 0; i < getViewString().length(); i++)
			border_box = border_box + "-";
		temp_str = "|" + getViewString() + " " + toString(m_value) + "|";
	}
	else {
		temp_str = getViewString() + " " + toString(m_value);
	}

	//Draw centered at position
	Vector pos = viewToWorld(getPosition());
	DM.drawString(pos, temp_str, CENTER_JUSTIFIED, m_color);

	// Draw box around display
	if (m_border) {
		DM.drawString(Vector(pos.getX(), pos.getY() - 1), border_box, CENTER_JUSTIFIED, m_color);
		DM.drawString(Vector(pos.getX(), pos.getY() + 1), border_box, CENTER_JUSTIFIED, m_color);
	}
	
}


int df::ViewObject::eventHandler(const Event *p_e) {
	//see if this is 'view' event
	if (p_e->getType() == VIEW_EVENT) {
		const EventView *p_ve = static_cast <const EventView *> (p_e);

		// See if this event is meant for this object
		if (p_ve->getTag() == getViewString()) {
			if (p_ve->getDelta()) {
				setValue(getValue() + p_ve->getValue());   //Change the value
			}
			else
				setValue(p_ve->getValue());                //New Value
		}
		return 1; // Event was handled
	}

	// If here, event not handled, call parent eventHandler()
	return 0;
}



df::ViewObjectLocation df::ViewObject::getLocation() const {
	return m_location;
}

void df::ViewObject::setValue(int new_value) {
	m_value = new_value;
}

int df::ViewObject::getValue() const {
	return m_value;
}

bool df::ViewObject::getBorder() const {
	return m_border;
}

void df::ViewObject::setColor(Color new_color) {
	m_color = new_color;
}

df::Color df::ViewObject::getColor() const {
	return m_color;
}

void df::ViewObject::setViewString(std::string new_view_string) {
	m_view_string = new_view_string;
}

std::string df::ViewObject::getViewString() const {
	return m_view_string;
}

void df::ViewObject::setDrawValue(bool new_draw_value) {
	m_draw_value = new_draw_value;
}

bool df::ViewObject::getDrawValue() const {
	return m_draw_value;
}