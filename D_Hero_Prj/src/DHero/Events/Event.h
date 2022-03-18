#pragma once
#include "dhpch.h"
#include "DHero/Core.h"

namespace DH {

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

// 宏参数前面加 '#'  会对宏参数进行字符串化操作，既前后各添加双引号；
// 宏参数前面加 '##' 会将两个 Token 连接为一个
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; } \
								virtual EventType GetEventType() const override { return GetStaticType(); } \
								virtual const char* GetName() const override {return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class DH_API Event {
	public:
		// 关键字 default: 定义默认虚构函数
		virtual ~Event() = default;

		bool Handled = false;

		// 常纯虚函数
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;

		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	protected:

	};

	// 事件分发器
	class DH_API EventDispatcher {
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {
		}

		template<typename T, typename F>
		bool Dispatcher(const F& func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				// static_cast 进行强制类型转换，
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}

}