#include "dhpch.h"
#include "Application.h"

#include "DHero/Core/Input.h"
#include "DHero/Core/TimeStep.h"
#include "DHero/Events/ApplicationEvent.h"
#include "DHero/Renderer/Renderer.h"
#include "DHero/Camera/OrthographicCamera.h"

#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace DH {

	Application* Application::s_Instance = nullptr;

	Application::Application()
	:m_LastFrameTime((float)glfwGetTime()), m_ImGuiLayer(nullptr){
				
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

	bool Application::OnWindowResize(WindowResizeEvent& e) {
		m_Window->OnResize(e.GetWidth(), e.GetHeight());
		return true;
	}

	void Application::OnEvent(Event& e) {

		EventDispatcher dispatcher(e);
		dispatcher.Dispatcher<WindowCloseEvent>(DH_BIND_EVENT_FN(Application, OnWindowClose));
		dispatcher.Dispatcher<WindowResizeEvent>(DH_BIND_EVENT_FN(Application, OnWindowResize));

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
		
		//WindowResizeEvent e(800, 800);
		//if(e.IsInCategory(EventCategoryApplication))
		//	DH_TRACE(e);


		while(m_Running) {
			float time = (float)glfwGetTime();
			TimeStep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (auto it : m_LayerStack)
				it->OnUpdate(timestep);

			if (m_ImGuiLayer) {
				m_ImGuiLayer->begin();
				for (auto it : m_LayerStack)
					it->OnImGuiRender();
				m_ImGuiLayer->end();
			}

			m_Window->OnUpdate();
		}
	}

}
