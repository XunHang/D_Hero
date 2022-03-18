#include <DHero.h>

class ExampleLayer :public DH::Layer {
public:
	ExampleLayer() 
	:Layer("Example"){

	}

	~ExampleLayer() {

	}

	void OnUpdate() override {
		DH_INFO("Example Layer Update");
	}

	void OnEvent(DH::Event& e) override {
		DH_TRACE("{0}", e);
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

//void main() {
//	SandBox* sandBox = new SandBox();
//	sandBox->Run();
//	delete sandBox;
//}