#include "dhpch.h"

#include "ExampleLayer.h"


ExampleLayer::ExampleLayer()
	:Layer("Example"), m_CameraController(){
	// vertex buffer
	float vertices_0[3 * (3 + 4)] = {
		-0.25f, -0.25f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f,
		 0.25f, -0.25f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
		 0.0f,   0.25f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
	};
	float vertices_1[(3+2) * 4] = {
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	};
	// index buffer
	unsigned int indices[6] = { 0, 1, 2, 0, 2, 3 };

	// 添加第一个绘制目标
	m_VertexArray_0.reset(DH::VertexArray::Create());
	std::shared_ptr<DH::VertexBuffer> m_VertBuffer_0 = std::shared_ptr<DH::VertexBuffer>(DH::VertexBuffer::Create(vertices_0, sizeof(vertices_0)));
	{
		DH::BufferLayout layout = {
			{DH::ShaderDataType::Float3, "a_Position"},
			{DH::ShaderDataType::Float4, "a_Color"},
		};
		m_VertBuffer_0->SetLayout(layout);
	}
	std::shared_ptr<DH::IndexBuffer> m_IndxBuffer = std::shared_ptr<DH::IndexBuffer>(DH::IndexBuffer::Create(indices, sizeof(indices) / 2));

	m_VertexArray_0->AddVertexBuffer(m_VertBuffer_0);
	m_VertexArray_0->AddIndexBuffer(m_IndxBuffer);

	// 添加第二个绘制目标
	m_VertexArray_1.reset(DH::VertexArray::Create());
	std::shared_ptr<DH::VertexBuffer> m_VertBuffer_1 = std::shared_ptr<DH::VertexBuffer>(DH::VertexBuffer::Create(vertices_1, sizeof(vertices_1)));
	{
		DH::BufferLayout layout = {
			{DH::ShaderDataType::Float3, "a_Position"},
			{DH::ShaderDataType::Float2, "a_Tex"},
		};
		m_VertBuffer_1->SetLayout(layout);
	}
	m_IndxBuffer.reset(DH::IndexBuffer::Create(indices, sizeof(indices)));
	m_VertexArray_1->AddVertexBuffer(m_VertBuffer_1);
	m_VertexArray_1->AddIndexBuffer(m_IndxBuffer);

	m_ShaderLibrary = std::make_shared<DH::ShaderLibrary>();
	m_ShaderLibrary->Load("D://git//D_Hero//shaders//flatColorShader.glsl");
	m_ShaderLibrary->Load("D://git//D_Hero//shaders//textureShader.glsl");

	m_Texture_0 = DH::Texture2D::Create("Assert/cat.png");
}

ExampleLayer::~ExampleLayer() {

}

void ExampleLayer::OnUpdate(DH::TimeStep& ts) {
	m_CameraController.OnUpdate(ts);

	DH::RenderCommand::Clear();
	DH::RenderCommand::ClearColor(m_FlatColor);

	glm::vec3 pos_0(0.5f, 0.0f, 0.0f);
	glm::vec3 pos_1(-0.5f, 0.0f, 0.0f);
	glm::mat4 transform_0 = glm::translate(glm::mat4(1.0f), pos_0);
	glm::mat4 transform_1 = glm::translate(glm::mat4(1.0f), pos_1);

	auto flatColorShader = m_ShaderLibrary->Get("flatColorShader");
	auto textureShader = m_ShaderLibrary->Get("textureShader");

	DH::Renderer::BeginScene(m_CameraController.GetCamera());
	{
		m_Texture_0->Bind(0);
		DH::Renderer::Submit(flatColorShader, m_VertexArray_0, transform_0);
		DH::Renderer::Submit(textureShader, m_VertexArray_1, transform_1);
	}
	DH::Renderer::EndScene();

}

void ExampleLayer::OnImGuiRender() {
	ImGui::Begin("Test");
	ImGui::Text("Hello World");
	ImGui::ColorEdit4("Flat Color Picker", glm::value_ptr(m_FlatColor));
	ImGui::End();
}

void ExampleLayer::OnEvent(DH::Event& e) {
	m_CameraController.OnEvent(e);
}
