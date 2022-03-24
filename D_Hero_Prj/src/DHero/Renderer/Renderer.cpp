#include "dhpch.h"

#include "Renderer.h"
#include "RenderCommand.h"

#include <glm/gtx/string_cast.hpp>
namespace DH {
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData();


	void Renderer::Init() {
		RenderCommand::Init();
	}

	void Renderer::BeginScene(OrthographicCamera& camera) {
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
		glm::mat4 tmp{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f};
		//s_SceneData->ViewProjectionMatrix = tmp;
		DH_CORE_INFO("{0}", glm::to_string(s_SceneData->ViewProjectionMatrix));
	}

	void Renderer::EndScene() {
	
	}
	
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray) {
		shader->Bind();
		shader->UploadUniformMat4("vp", s_SceneData->ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}