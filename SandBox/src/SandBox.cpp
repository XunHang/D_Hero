#include <DHero.h>

#include "imgui.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

glm::mat4 camera(float Translate, glm::vec2 const& Rotate) {
	glm::mat4 res = glm::mat4(1.0f);
	return res;
}


class ExampleLayer :public DH::Layer {
public:
	ExampleLayer() 
	:Layer("Example"){

	}

	~ExampleLayer() {

	}

	void OnUpdate() override {
		//DH_INFO("Example Layer Update");
		if (DH::Input::IsKeyPressed(DH::Key::Space))
			DH_INFO("Space Button is pressed.");
	}

	void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello world.");
		ImGui::End();
	}

	void OnEvent(DH::Event& e) override {
		//DH_TRACE("{0}", e);
		if (e.GetEventType() == DH::EventType::KeyPressed) {
			DH::KeyPressedEvent& ke = (DH::KeyPressedEvent&)e;
			DH_TRACE("{0}", (char)ke.GetKeyCode());
		}
	}
};

class SandBox :public DH::Application {
public:
	SandBox() {
		PushLayer(new ExampleLayer());
	}
	~SandBox() {

	}
};

DH::Application* DH::CreaterApplication() {
	return new SandBox();
}
