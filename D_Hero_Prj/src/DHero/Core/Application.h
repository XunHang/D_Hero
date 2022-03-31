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
		float m_LastFrameTime;

		static Application* s_Instance;

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	};

	// To Do by Client.
	Application* CreaterApplication();

}

