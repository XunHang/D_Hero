#pragma once
#include "DHero.h"
#include "imgui.h"

class ExampleLayer :public DH::Layer {
public:
	ExampleLayer();
	~ExampleLayer();

private:
	void OnUpdate(DH::TimeStep& ts) override;
	void OnImGuiRender() override;
	void OnEvent(DH::Event& e) override;

	DH::OrthographicCamera m_Camera;
	std::shared_ptr<DH::ShaderLibrary> m_ShaderLibrary;
	std::shared_ptr<DH::Texture2D> m_Texture_0;
	std::shared_ptr<DH::VertexArray> m_VertexArray_0;
	std::shared_ptr<DH::VertexArray> m_VertexArray_1;

	glm::vec4 m_FlatColor = glm::vec4(0.2, 0.3, 0.8, 1.0);
};