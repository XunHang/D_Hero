#include <DHero.h>

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
		PushLayer(new DH::ImGuiLayer());
	}
	~SandBox() {

	}
};

DH::Application* DH::CreaterApplication() {
	return new SandBox();
}
