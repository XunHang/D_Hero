#include "dhpch.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"


namespace DH {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

	void RenderCommand::Init() {
		s_RendererAPI->Init();
	}

	void RenderCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
		s_RendererAPI->DrawIndexed(vertexArray);
	}

	void RenderCommand::Clear() {
		s_RendererAPI->Clear();
	}

	void RenderCommand::ClearColor(const glm::vec4& color) {
		s_RendererAPI->ClearColor(color);
	}
}