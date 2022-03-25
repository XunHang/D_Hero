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
		s_SceneData->View = camera.GetViewMatrix();
		s_SceneData->Projection= camera.GetProjectionMatrix();
	}

	void Renderer::EndScene() {
	
	}
	
	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& model) {
		shader->Bind();
		//shader->UploadUniform1i("ourTexture", 0);
		shader->UploadUniformMat4("model", model);
		//shader->UploadUniformMat4("view", s_SceneData->View);
		//shader->UploadUniformMat4("projection", s_SceneData->Projection);
		shader->UploadUniformMat4("vp", s_SceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}

