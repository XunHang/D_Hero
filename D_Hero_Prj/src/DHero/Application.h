#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "DHero/LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include "DHero/Renderer/Shader.h"
#include "DHero/Renderer/Buffer.h"

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

		unsigned int m_VertArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertBuffer;
		std::unique_ptr<IndexBuffer> m_IndxBuffer;

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		static Application* s_Instance;
	};

	// To Do by Client.
	Application* CreaterApplication();

}

