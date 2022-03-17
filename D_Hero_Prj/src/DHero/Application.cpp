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

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher(e);
		dispatcher.Dispatcher<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		//DH_CORE_TRACE("{0}", e);

		// 反向遍历层来获取事件，因为层的渲染是自下而上的，但是交互操作的逻辑是自上而下的；
		// 当上层将事件捕获并处理后，事件就不再向下传递；
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			it--;			
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
		//for (Layer* layer : m_LayerStack) {
		//	layer->OnEvent(e);
		//	if (e.Handled)
		//		break;
		//}
	}

	void Application::Run() {
		
		WindowResizeEvent e(1024, 768);
		if(e.IsInCategory(EventCategoryApplication))
			DH_TRACE(e);

		while(m_Running) {
			for (auto it : m_LayerStack)
				it->OnUpdate();

			m_Window->OnUpdate();
		}
	}

}
