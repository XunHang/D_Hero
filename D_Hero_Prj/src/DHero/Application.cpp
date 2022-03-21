#include "dhpch.h"
#include "Application.h"

#include "DHero/Events/ApplicationEvent.h"
#include "DHero/Input.h"

#include "glm/glm.hpp"
#include "glad/glad.h"

namespace DH {

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		DH_ASSERT(!s_Instance, "Application already inited.");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(DH_BIND_EVENT_FN(Application, OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
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

		// 反向遍历层来获取事件，因为层的渲染是自下而上的，但是交互操作的逻辑是自上而下的；
		// 当上层将事件捕获并处理后，事件就不再向下传递；
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
			//glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			for (auto it : m_LayerStack)
				it->OnUpdate();

			m_ImGuiLayer->begin();
			for (auto it : m_LayerStack)
				it->OnImGuiRender();
			m_ImGuiLayer->end();

			//auto [x, y] = Input::GetMousePosition();
			//DH_TRACE("{0}, {1}", x, y);

			m_Window->OnUpdate();
		}
	}

}
