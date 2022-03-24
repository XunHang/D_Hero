#include "dhpch.h"
#include "Application.h"

#include "DHero/Events/ApplicationEvent.h"
#include "DHero/Core/Input.h"
#include "DHero/Renderer/Renderer.h"

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

		// vertex buffer
		float vertices_0[3 * (3+4)] = {
			-0.25f, -0.25f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f,
			 0.25f, -0.25f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,   0.25f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
		};
		float vertices_1[3 * 4] = {
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
		};
		// index buffer
		unsigned int indices[6] = { 0, 1, 2, 0, 2, 3 };

		// 添加第一个绘制目标
		//m_VertArray_0 = std::make_shared<VertexArray>(VertexArray::Create());
		//m_VertBuffer_0 = std::make_shared<VertexBuffer>(VertexBuffer::Create(vertices_0, sizeof(vertices_0)));
		m_VertArray_0.reset(VertexArray::Create());
		m_VertBuffer_0.reset(VertexBuffer::Create(vertices_0, sizeof(vertices_0)));
		{
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"},
			};
			m_VertBuffer_0->SetLayout(layout);
		}
		//m_IndxBuffer = std::make_shared<IndexBuffer>(IndexBuffer::Create(indices, sizeof(indices)));
		m_IndxBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/2));
		m_VertArray_0->AddVertexBuffer(m_VertBuffer_0);
		m_VertArray_0->AddIndexBuffer(m_IndxBuffer);

		// 添加第二个绘制目标
		//m_VertArray_1 = std::make_shared<VertexArray>(VertexArray::Create());
		//m_VertBuffer_1 = std::make_shared<VertexBuffer>(VertexBuffer::Create(vertices_1, sizeof(vertices_1)));
		m_VertArray_1.reset(VertexArray::Create());
		m_VertBuffer_1.reset(VertexBuffer::Create(vertices_1, sizeof(vertices_1)));
		{
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
			};
			m_VertBuffer_1->SetLayout(layout);
		}
		m_IndxBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)));
		m_VertArray_1->AddVertexBuffer(m_VertBuffer_1);
		m_VertArray_1->AddIndexBuffer(m_IndxBuffer);

		// Bind Shader
		std::string vertexShader = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 model;
			uniform mat4 view;
			uniform mat4 projection;
			uniform mat4 vp;

			out vec4 m_Color;

			void main () {
				m_Color = a_Color;
				//gl_Position = projection * view * model * vec4(a_Position, 1.0);
				gl_Position = vp * model * vec4(a_Position, 1.0);
			}			
		)";
		std::string fragmentShader_0 = R"(
			#version 330 core
			
			in vec4 m_Color;
			out vec4 color;

			void main () {
				color = m_Color;
			}			
		)";
		std::string fragmentShader_1 = R"(
			#version 330 core
			
			out vec4 color;

			void main () {
				color = vec4(0.8, 0.2, 0.0, 1.0);
			}			
		)";

		m_Shader_0.reset(new Shader(vertexShader, fragmentShader_0));
		m_Shader_1.reset(new Shader(vertexShader, fragmentShader_1));
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

#include "DHero/Camera/OrthographicCamera.h"
#include <glm/glm.hpp>
	void Application::Run() {
		
		WindowResizeEvent e(1024, 768);
		if(e.IsInCategory(EventCategoryApplication))
			DH_TRACE(e);

		OrthographicCamera* camera = new OrthographicCamera(-1, 1, -1, 1);

		while(m_Running) {
			RenderCommand::Clear();
			RenderCommand::ClearColor({ 0.2f, 0.2f, 0.2f, 1.0f});
			
			glm::vec3 pos(0.0f, 0.0f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);

			Renderer::BeginScene(*camera);
			{
				Renderer::Submit(m_Shader_1, m_VertArray_1, transform);

				Renderer::Submit(m_Shader_0, m_VertArray_0, transform);
			}
			Renderer::EndScene();


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
