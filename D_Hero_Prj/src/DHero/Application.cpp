#include "dhpch.h"
#include "Application.h"

#include "DHero/Events/ApplicationEvent.h"


namespace DH {

	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application() {

	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher(e);
		dispatcher.Dispatcher<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		DH_CORE_TRACE("{0}", e);
	}

	void Application::Run() {
		
		WindowResizeEvent e(1024, 768);
		if(e.IsInCategory(EventCategoryApplication))
			DH_TRACE(e);
		while(m_Running) {
			m_Window->OnUpdate();
		}
	}

}
