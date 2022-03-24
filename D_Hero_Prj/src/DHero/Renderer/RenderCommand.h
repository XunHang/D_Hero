#pragma once

#include "DHero/Core/Core.h"

#include "RendererAPI.h"

namespace DH {

	// ����Ⱦ���Ϊ��������Ϊ������мܹ���׼��
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