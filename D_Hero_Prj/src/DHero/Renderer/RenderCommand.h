#pragma once

#include "DHero/Core/Core.h"

#include "RendererAPI.h"

namespace DH {

	// 将渲染拆分为具体的命令，为命令队列架构做准备
	class DH_API RenderCommand {
	public:
		static void Init();
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
		static void Clear();
		static void ClearColor(const glm::vec4&);

	private:
		static RendererAPI* s_RendererAPI;
	};
}