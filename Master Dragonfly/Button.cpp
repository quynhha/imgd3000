#include "Button.h"
#include "EventMouse.h"
#include "utility.h"

// Define registerInterest in case engine does not.
static void registerInterest(std::string s) {};

df::Button::Button()
{
    setHighlightColor(df::RED);
    setDefaultColor(df::WHITE);
    setType("Button");
    registerInterest(df::MSE_EVENT);
}

int df::Button::eventHandler(const Event* p_e)
{
    if (p_e->getType() != df::MSE_EVENT)
    {
        return 0;
    }
    const EventMouse* p_e_m = dynamic_cast <const df::EventMouse*> (p_e);
    if (mouseOverButton(p_e_m))
    {
        setColor(m_highlight_color);

        if (p_e_m->getMouseAction() == CLICKED)
        {
            callback();
        }
        setColor(m_default_color);

        return 1; 
    }
}

void df::Button::setHighlightColor(Color new_highlight_color)
{
    m_highlight_color = new_highlight_color; 
}

df::Color df::Button::getHighlightColor() const
{
    return m_highlight_color;
}

void df::Button::setDefaultColor(Color new_default_color)
{
    m_default_color = new_default_color;
}

df::Color df::Button::getDefaultColor() const
{
    return m_default_color;
}

bool df::Button::mouseOverButton(const EventMouse* p_e) const
{
   auto width = getViewString().size();
   auto height = 1; 
   if (getBorder())
   {
       width = width + 4; 
       height = height + 2; 

   }
   Vector corner(getPosition().getX() - width / 2, getPosition().getY() - height / 2); 
   Box b(corner, width, height);
   if (boxContainsPosition(b, p_e->getMousePosition()))
   {
       return true;
   }
   else
   {
        return false;
   }
   
}
