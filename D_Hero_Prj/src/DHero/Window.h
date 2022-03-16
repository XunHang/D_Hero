#pragma once

#include "dhpch.h"

#include "DHero/Core.h"
#include "DHero/Events/Event.h"

namespace DH {

	struct WindowProps {
		std::string Title;
		unsigned int Width, Height;

		WindowProps(const std::string& title = "DH-Engine", 
					unsigned int width = 1280, 
					unsigned int height = 720)
			:Title(title), Width(width), Height(height) {
		}
	};

	// 定义抽象窗口接口，由各个平台具体进行实现
	class DH_API Window {
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enbaled) = 0;
		virtual bool IsVSync() const = 0;

		// 定义窗口创建接口
		static Window* Create(const WindowProps& props = WindowProps());
	};

}