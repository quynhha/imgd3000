//Thi Quynh Ha Nguyen - Master Dragonfly
/*
Animation.cpp
*/

#include "Animation.h"


// Animation constructor
df::Animation::Animation()
{
}

// Set associated Sprite to new one.
// Note, Sprite is managed by ResourceManager.
// Set Sprite index to 0 (first frame).
void df::Animation::setSprite(Sprite* p_new_sprite) {
	m_p_sprite = p_new_sprite;
}

// Return pointer to associated Sprite.
df::Sprite* df::Animation::getSprite() const {
	return m_p_sprite;
}
// Set Sprite name (in ResourceManager).
void df::Animation::setName(std::string new_name) {
	m_name = new_name;
}

// Get Sprite name (in ResourceManager).
std::string df::Animation::getName() const {
	return m_name;
}

// Set index of current Sprite frame to be displayed.
void df::Animation::setIndex(int new_index) {
	m_index = new_index;
}

// Get index of current Sprite frame to be displayed.
int df::Animation::getIndex() const {
	return m_index;
}

// Set animation slowdown count (-1 means stop animation).
void df::Animation::setSlowdownCount(int new_slowdown_count) {
	m_slowdown_count = new_slowdown_count;
}

// Set animation slowdown count (-1 means stop animation).
int df::Animation::getSlowdownCount() const {
	return m_slowdown_count;
}

// Draw single frame centered at position (x,y).
// Drawing accounts for slowdown, and advances Sprite frame.
// Return 0 if ok, else -1.
int df::Animation::draw(Vector position) {
	// If sprite not defined, don't continue further.
	if (m_p_sprite == NULL)
	{
		return 0;
	}

	// Ask Sprite to draw current frame.
	int index = getIndex();
	Sprite* newSprite = new Sprite(index);
	newSprite->draw(index, position);

	// If slowdown count is -1, then animation is frozen.
	if (getSlowdownCount() == -1) {
		return 0;
	}
	// Increment counter.
	int count = getSlowdownCount();
	count++;

	// Advance sprite index, if appropriate.
	if (count >= newSprite->getSlowdown()) {
		count = 0; // Reset counter.
		index++;  // Advance frame.

		// If at last frame, loop to beginning.
		if (index >= m_p_sprite->getFrameCount()) {
			index = 0;
		}
		setIndex(index);
	}

	// Set counter for next draw().
	setSlowdownCount(count);
	return 0;

}
df::Box df::Animation::getBox() const {
	if (!m_p_sprite)
	{
		Box box(Vector(-0.5, -0.5), 0.99, 0.99);
		return box;
	}
	Vector corner((-1) * m_p_sprite->getWidth() / 2.0, (-1) * m_p_sprite->getHeight() / 2.0);
	Box box(corner, m_p_sprite->getWidth(), m_p_sprite->getHeight());
	return box;
}
