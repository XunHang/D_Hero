#include "dhpch.h"
#include "Renderer2D.h"

namespace DH {
	struct SceneData2D {
		glm::mat4 ViewProjectionMatrix;
	};

	struct RendererData2D {
		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<Shader> CommonShader;
		std::shared_ptr<Texture> WhiteTexture;
	};

	static SceneData2D* s_SceneData2D;
	static RendererData2D* s_RendererData2D;

	void Renderer2D::Init() {
		s_SceneData2D = new SceneData2D();
		s_RendererData2D = new RendererData2D();

		// 初始化一个基础的举行顶点
		float vertices[(3 + 2) * 4] = {
			 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		};
		unsigned int indices[6] = { 0, 1, 2, 0, 2, 3 };

		s_RendererData2D->QuadVertexArray.reset(VertexArray::Create());
		auto m_VertBuffer = std::shared_ptr<VertexBuffer>(VertexBuffer::Create(vertices, sizeof(vertices)));
		{
			DH::BufferLayout layout = {
				{DH::ShaderDataType::Float3, "a_Position"},
				{DH::ShaderDataType::Float2, "a_Tex"},
			};
			m_VertBuffer->SetLayout(layout);
		}
		auto m_IndxBuffer = std::shared_ptr<IndexBuffer>(DH::IndexBuffer::Create(indices, sizeof(indices)));

		s_RendererData2D->QuadVertexArray->AddVertexBuffer(m_VertBuffer);
		s_RendererData2D->QuadVertexArray->AddIndexBuffer(m_IndxBuffer);

		s_RendererData2D->CommonShader = Shader::Create("D://git//D_Hero//shaders//commonShader.glsl");
		s_RendererData2D->WhiteTexture = Texture2D::Create("Assert/white.png");
	}

	void Renderer2D::BeginScene(OrthographicCamera& camera) {
		s_SceneData2D->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		s_RendererData2D->CommonShader->Bind();
		s_RendererData2D->CommonShader->UploadUniformMat4("u_VPmatrix",s_SceneData2D->ViewProjectionMatrix);
	}

	void Renderer2D::EndScene()	{

	}


	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
		s_RendererData2D->WhiteTexture->Bind(0);
		s_RendererData2D->CommonShader->UploadUniformVec4("u_Color", color);

		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::scale(transform, glm::vec3(size.x, size.y, 1.0f));
		s_RendererData2D->CommonShader->UploadUniformMat4("u_Transform", transform);

		RenderCommand::DrawIndexed(s_RendererData2D->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad(glm::vec3(position.x, position.y, 1.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, std::shared_ptr<Texture> texture) {
		texture->Bind(0);
		s_RendererData2D->CommonShader->UploadUniformVec4("u_Color", {1.0f, 1.0f, 1.0f, 1.0f});

		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, position);
		transform = glm::scale(transform, glm::vec3(size.x, size.y, 1.0f));
		s_RendererData2D->CommonShader->UploadUniformMat4("u_Transform", transform);

		RenderCommand::DrawIndexed(s_RendererData2D->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, std::shared_ptr<Texture> texture) {
		DrawQuad(glm::vec3(position.x, position.y, 1.0f), size, texture);
	}
}