#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "DHero/LayerStack.h"


namespace DH {

	class DH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To Do by Client.
	Application* CreaterApplication();

}

