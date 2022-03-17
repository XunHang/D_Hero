#pragma once

#include "DHero/Events/Event.h"
#include "DHero/Events/MouseCodes.h"


namespace DH {

	class DH_API MouseMovedEvent :public Event {
	public:
		MouseMovedEvent(float xPos, float yPos)
			:m_PosX(xPos), m_PosY(yPos) {}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

		inline float GetXPos() const { return m_PosX; }
		inline float GetYPos() const { return m_PosY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent:\n X Pos: " << m_PosX << " Y Pos: " << m_PosY;
			return ss.str();
		}

	private:
		float m_PosX, m_PosY;
	};

	class DH_API MouseButtonEvent :public Event {
	public:
		MouseButtonEvent(MouseCode button)
			:m_Button(button){}

		virtual ~MouseButtonEvent() {};
		inline MouseCode GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouseButton)
	protected:
		MouseCode m_Button;
	};

	class DH_API MouseButtonPressedEvent :public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(MouseCode button) :
			MouseButtonEvent(button) {}

		EVENT_CLASS_TYPE(MouseButtonPressed)

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent:\n MouseCode: " <<m_Button;
			return ss.str();
		}

	};

	class DH_API MouseButtonReleasedEvent :public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(MouseCode button) :
			MouseButtonEvent(button) {}

		EVENT_CLASS_TYPE(MouseButtonReleased)

			std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent:\n MouseCode: " << m_Button;
			return ss.str();
		}

	};

	class DH_API MouseScrolledEvent :public Event {
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			:m_XOffset(xOffset), m_YOffset(yOffset) {}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolled:\n X Pos: " << m_XOffset << " Y Pos: " << m_YOffset;
			return ss.str();
		}

	private:
		float m_XOffset, m_YOffset;
	};

}