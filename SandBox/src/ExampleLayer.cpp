#include "dhpch.h"

#include "ExampleLayer.h"


ExampleLayer::ExampleLayer()
	:Layer("Example"), m_Camera(-2, 2, -1.5, 1.5) {
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
	//m_VertBuffer_0.reset(VertexBuffer::Create(vertices_0, sizeof(vertices_0)));
	{
		DH::BufferLayout layout = {
			{DH::ShaderDataType::Float3, "a_Position"},
			{DH::ShaderDataType::Float4, "a_Color"},
		};
		m_VertBuffer_0->SetLayout(layout);
	}
	std::shared_ptr<DH::IndexBuffer> m_IndxBuffer = std::shared_ptr<DH::IndexBuffer>(DH::IndexBuffer::Create(indices, sizeof(indices) / 2));
	//m_IndxBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / 2));
	m_VertexArray_0->AddVertexBuffer(m_VertBuffer_0);
	m_VertexArray_0->AddIndexBuffer(m_IndxBuffer);

	// 添加第二个绘制目标
	//m_VertArray_1 = std::make_shared<VertexArray>(VertexArray::Create());
	//m_VertBuffer_1 = std::make_shared<VertexBuffer>(VertexBuffer::Create(vertices_1, sizeof(vertices_1)));
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

	// Bind Shader
	std::string vertexShader = R"(
		#version 330 core
		
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;
		layout (location = 2) in vec2 a_Tex;

		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;
		uniform mat4 vp;

		out vec4 m_Color;
		out vec2 texCoord;

		void main () {
			m_Color = a_Color;
			//gl_Position = projection * view * model * vec4(a_Position, 1.0);
			gl_Position = vp * model * vec4(a_Position, 1.0);
			texCoord = a_Tex;
		}			
	)";
	std::string vertexShader2 = R"(
		#version 330 core
		
		layout(location = 0) in vec3 a_Position;
		layout (location = 1) in vec2 a_Tex;

		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;
		uniform mat4 vp;

		out vec2 texCoord;

		void main () {
			//gl_Position = projection * view * model * vec4(a_Position, 1.0);
			gl_Position = vp * model * vec4(a_Position, 1.0);
			texCoord = a_Tex;
		}			
	)";
	std::string fragmentShader_0 = R"(
		#version 330 core
			
		in vec4 m_Color;

		out vec4 color;

		void main () {
			color = m_Color;
		}			
	)";
	std::string fragmentShader_1 = R"(
		#version 330 core
			
		in vec2 texCoord;
		uniform sampler2D ourTexture;

		out vec4 color;

		void main () {
			color = texture(ourTexture, texCoord);
		}			
	)";

	m_Shader_0.reset(new DH::Shader(vertexShader, fragmentShader_0));
	m_Shader_1.reset(new DH::Shader(vertexShader2, fragmentShader_1));

	m_Texture_0.reset(DH::Texture2D::Create("Assert/cat.png"));
	//m_Texture_0 = DH::Texture2D::Create(10,10);
}

ExampleLayer::~ExampleLayer() {

}

void ExampleLayer::OnUpdate(DH::TimeStep& ts) {

	DH::RenderCommand::Clear();
	DH::RenderCommand::ClearColor(m_FlatColor);

	glm::vec3 pos(0.0f, 0.0f, 0.0f);
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);

	DH::Renderer::BeginScene(m_Camera);
	{
		m_Texture_0->Bind(0);
		DH::Renderer::Submit(m_Shader_1, m_VertexArray_1, transform);

		DH::Renderer::Submit(m_Shader_0, m_VertexArray_0, transform);
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
}
