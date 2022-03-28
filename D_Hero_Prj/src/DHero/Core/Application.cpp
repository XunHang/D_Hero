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

	Application::Application() {
		m_LastFrameTime = (float)glfwGetTime();


		
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
		
		//WindowResizeEvent e(800, 800);
		//if(e.IsInCategory(EventCategoryApplication))
		//	DH_TRACE(e);


		while(m_Running) {
			float time = (float)glfwGetTime();
			TimeStep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (auto it : m_LayerStack)
				it->OnUpdate(timestep);

			m_ImGuiLayer->begin();
			for (auto it : m_LayerStack)
				it->OnImGuiRender();
			m_ImGuiLayer->end();


			m_Window->OnUpdate();
		}
	}

}
