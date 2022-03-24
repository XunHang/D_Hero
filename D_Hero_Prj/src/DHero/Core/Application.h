#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"

#include "DHero/Events/Event.h"
#include "DHero/ImGui/ImGuiLayer.h"

#include "DHero/Renderer/Shader.h"
#include "DHero/Renderer/Buffer.h"
#include "DHero/Renderer/VertexArray.h"

namespace DH {

	class DH_API Application
	{
	public:
		Application();
		virtual ~Application();
		inline static Application& Get() { return *s_Instance; }

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() const { return *m_Window; }

	protected:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		std::shared_ptr<VertexArray> m_VertArray_0;
		std::shared_ptr<VertexArray> m_VertArray_1;
		std::shared_ptr<Shader> m_Shader_0;
		std::shared_ptr<Shader> m_Shader_1;
		std::shared_ptr<VertexBuffer> m_VertBuffer_0;
		std::shared_ptr<VertexBuffer> m_VertBuffer_1;
		std::shared_ptr<IndexBuffer> m_IndxBuffer;

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		static Application* s_Instance;
	};

	// To Do by Client.
	Application* CreaterApplication();

}

