#include "dhpch.h"
#include "Application.h"

#include "DHero/Events/ApplicationEvent.h"
#include "DHero/Input.h"

namespace DH {

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		DH_ASSERT(!s_Instance, "Application already inited.");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(DH_BIND_EVENT_FN(Application, OnEvent));
	}

	Application::~Application() {

	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher(e);
		dispatcher.Dispatcher<WindowCloseEvent>(DH_BIND_EVENT_FN(Application, OnWindowClose));

		//DH_CORE_TRACE("{0}", e);

		// �������������ȡ�¼�����Ϊ�����Ⱦ�����¶��ϵģ����ǽ����������߼������϶��µģ�
		// ���ϲ㽫�¼����񲢴�����¼��Ͳ������´��ݣ�
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			it--;			
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run() {
		
		WindowResizeEvent e(1024, 768);
		if(e.IsInCategory(EventCategoryApplication))
			DH_TRACE(e);

		while(m_Running) {

			for (auto it : m_LayerStack)
				it->OnUpdate();

			//auto [x, y] = Input::GetMousePosition();
			//DH_TRACE("{0}, {1}", x, y);

			m_Window->OnUpdate();
		}
	}

}
