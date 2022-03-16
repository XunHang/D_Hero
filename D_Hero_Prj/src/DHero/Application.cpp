#include "dhpch.h"
#include "Application.h"

#include "DHero/Events/ApplicationEvent.h"
#include "DHero/Log.h"


namespace DH {

	Application::Application() {
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application() {

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
