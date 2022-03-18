#include "dhpch.h"

#include "ImGuiLayer.h"
#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRender.h"

#include "GLFW/glfw3.h"
#include "DHero/Application.h"

namespace DH {
	ImGuiLayer::ImGuiLayer() 
		:Layer("ImGuiLayer"){

	}

	ImGuiLayer::~ImGuiLayer() {

	}

	void ImGuiLayer::OnAttach()	{
		ImGui::CreateContext();
		
		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;


		//ImGui::StyleColorsDark();		// Choose your favorite style.
		ImGui::StyleColorsClassic();

		ImGui_ImplOpenGL3_Init("#version 330");
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate() {
		ImGui_ImplOpenGL3_NewFrame();

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		ImGui::NewFrame();

		ImGui::ShowDemoWindow();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	
	void ImGuiLayer::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatcher<MouseButtonPressedEvent>(DH_BIND_EVENT_FN(ImGuiLayer, OnMouseButtonPressedEvent));
		dispatcher.Dispatcher<MouseButtonReleasedEvent>(DH_BIND_EVENT_FN(ImGuiLayer, OnMouseButtonReleasedEvent));
		dispatcher.Dispatcher<MouseMovedEvent>(DH_BIND_EVENT_FN(ImGuiLayer, OnMouseMovedEvent));
		dispatcher.Dispatcher<MouseScrolledEvent>(DH_BIND_EVENT_FN(ImGuiLayer, OnMouseScrolledEvent));
		dispatcher.Dispatcher<KeyTypedEvent>(DH_BIND_EVENT_FN(ImGuiLayer, OnKeyTypedEvent));
		dispatcher.Dispatcher<KeyPressedEvent>(DH_BIND_EVENT_FN(ImGuiLayer, OnKeyPressedEvent));
		dispatcher.Dispatcher<KeyReleasedEvent>(DH_BIND_EVENT_FN(ImGuiLayer, OnKeyReleasedEvent));
		dispatcher.Dispatcher<WindowResizeEvent>(DH_BIND_EVENT_FN(ImGuiLayer, OnWindowResizeEvent));


	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2((float)e.GetXPos(), (float)e.GetYPos());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel  += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(e.GetKeyCode());

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e) {
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)e.GetWidth(), (float)e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		//glViewPort(0, 0, )

		return false;
	}

}