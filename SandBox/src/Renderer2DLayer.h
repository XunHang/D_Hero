#pragma once
#include "DHero.h"
#include "imgui.h"

class Renderer2DLayer :public DH::Layer {
public:
	Renderer2DLayer();
	~Renderer2DLayer();

private:
	void OnUpdate(DH::TimeStep& ts) override;
	void OnImGuiRender() override;
	void OnEvent(DH::Event& e) override;

	DH::OrthographicCameraController m_CameraController;
	std::shared_ptr<DH::Texture2D> m_Texture;

	glm::vec4 m_FlatColor = glm::vec4(0.2, 0.3, 0.8, 1.0);
};