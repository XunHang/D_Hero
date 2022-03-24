#include <DHero.h>
// ---------- Entry Point ----------
#include "DHero/Core/EntryPoint.h"
// ---------------------------------

#include "ExampleLayer.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

glm::mat4 camera(float Translate, glm::vec2 const& Rotate) {
	glm::mat4 res = glm::mat4(1.0f);
	return res;
}

class SandBox :public DH::Application {
public:
	SandBox() {
		DH_ASSERT(!s_Instance, "Application already inited.");
		s_Instance = this;

		m_Window = std::unique_ptr<DH::Window>(DH::Window::Create());
		m_Window->SetEventCallback(DH_BIND_EVENT_FN(Application, OnEvent));

		m_ImGuiLayer = new DH::ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		PushLayer(new ExampleLayer());
	}
	~SandBox() {

	}
};

DH::Application* DH::CreaterApplication() {
	return new SandBox();
}
