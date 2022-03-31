#include "dhpch.h"

#include "Renderer2DLayer.h"


Renderer2DLayer::Renderer2DLayer()
	:Layer("Renderer2D"), m_CameraController() {
	DH::Renderer2D::Init();
	m_Texture = DH::Texture2D::Create("Assert/cat.png");
}

Renderer2DLayer::~Renderer2DLayer() {

}

void Renderer2DLayer::OnUpdate(DH::TimeStep& ts) {
	m_CameraController.OnUpdate(ts);

	DH::RenderCommand::Clear();
	DH::RenderCommand::ClearColor(m_FlatColor);

	glm::vec3 pos(0.5f, 0.0f, 0.0f);
	glm::vec3 pos_0( 0.7f, 0.0f, 0.0f);	
	glm::vec3 pos_1(-0.7f, 0.0f, 0.0f);

	DH::Renderer2D::BeginScene(m_CameraController.GetCamera());
	{
		DH::Renderer2D::DrawQuad(pos, { 1.5f, 1.0f }, { 1.0f, 0.0f, 1.0f, 0.0f });
		DH::Renderer2D::DrawQuad(pos, { 1.0f, 0.5f }, m_Texture);
	}
	DH::Renderer2D::EndScene();

}

void Renderer2DLayer::OnImGuiRender() {
	//ImGui::Begin("Test2D");
	//ImGui::Text("Hello World 2D Renderer");
	//ImGui::ColorEdit4("Flat Color Picker", glm::value_ptr(m_FlatColor));
	//ImGui::End();
}

void Renderer2DLayer::OnEvent(DH::Event& e) {
	m_CameraController.OnEvent(e);
}
