#pragma once

#include "DHero/Core/Window.h"
#include "DHero/Renderer/GraphicsContext.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

namespace DH {

	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override {
			m_Data.EventCallback = callback;
		}
		void SetVSync(bool Enbale) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
		virtual void OnResize(unsigned int width, unsigned int height);
	};

}