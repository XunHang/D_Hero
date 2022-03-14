#pragma once

#include "DHero/Events/KeyCodes.h"
#include "DHero/Events/Event.h"

namespace DH {

	class KeyEvent : public Event {
	public:
		KeyCode GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeybord | EventCategoryInput);

	protected:
		KeyCode m_KeyCode;
		KeyEvent(const KeyCode keycode)
			:m_KeyCode(keycode) {}
	};


}