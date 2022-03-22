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

		// vertex array
		glGenVertexArrays(1, &m_VertArray);
		glBindVertexArray(m_VertArray);
		// vertex buffer
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f,
		};

		m_VertBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VertBuffer->Bind();		

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		// index buffer
		unsigned int indices[3] = { 0,1,2 };
		m_IndxBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)));
		m_IndxBuffer->Bind();

		// Bind Shader
		std::string vertexShader = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;

			void main () {
				gl_Position = vec4(a_Position, 1.0);
			}			
		)";
		std::string fragmentShader = R"(
			#version 330 core
		
			out vec4 color;

			void main () {
				color = vec4(0.8, 0.2, 0.3, 1.0);
			}			
		)";

		m_Shader.reset(new Shader(vertexShader, fragmentShader));
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

			glBindVertexArray(m_VertArray);
			m_Shader->Bind();
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
