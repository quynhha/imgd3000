#ifndef __BUTTON_H__
#define __BUTTON_H__

// Engine includes.
#include "EventMouse.h"    
#include "ViewObject.h"

namespace df {

	class Button : public ViewObject {

	private:
		Color m_highlight_color;	 ///< Color when highlighted.
		Color m_default_color;	 ///< Color when not highlighted.

	public:
		Button();

		/// Handle "mouse" events.
		/// Return 0 if ignored, else 1.
		int eventHandler(const Event* p_e);

		/// Set highlight (when mouse over) color for Button.
		void setHighlightColor(Color new_highlight_color);

		/// Get highlight (when mouse over) color for Button.
		Color getHighlightColor() const;

		/// Set color of Button.
		void setDefaultColor(Color new_default_color);

		/// Get color of Button
		Color getDefaultColor() const;

		/// Return true if mouse over Button, else false. 
		bool mouseOverButton(const EventMouse* p_e) const;

		/// Called when Button clicked.
		/// Must be defined by derived class.
		virtual void callback() = 0;

	};

} // end of namespace df
#endif
