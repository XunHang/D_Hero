#pragma once

#include "DHero/Events/Event.h"
#include "DHero/Events/KeyCodes.h"

namespace DH {

	class DH_API KeyEvent : public Event {
	public:
		KeyCode GetKeyCode() const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyCode m_KeyCode;
		KeyEvent(const KeyCode keycode)
			:m_KeyCode(keycode) {}
	};

	class DH_API KeyPressedEvent :public KeyEvent {
	public:
		KeyPressedEvent(KeyCode keycode, int keyRepeated)
			:KeyEvent(keycode), m_KeyRepeated(keyRepeated) {}

		inline int GetRepeated() const { return m_KeyRepeated; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent:\n KeyCode: " << m_KeyCode << " KeyRepeated: " << m_KeyRepeated;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)

	protected:
		unsigned int m_KeyRepeated;
	};

	class DH_API KeyReleasedEvent :public KeyEvent {
	public:
		KeyReleasedEvent(KeyCode keycode)
			:KeyEvent(keycode){}


		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent:\n KeyCode: " << m_KeyCode ;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	protected:
	};

}