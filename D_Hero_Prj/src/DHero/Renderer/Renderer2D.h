#pragma once
#include "DHero/Core/Core.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Buffer.h"
#include "Texture.h"
#include "RenderCommand.h"
#include "RendererAPI.h"
#include "DHero/Camera/OrthographicCamera.h"

#include <glm/glm.hpp>

namespace DH {


	class DH_API Renderer2D {
	public:
		static void Init();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, std::shared_ptr<Texture> texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, std::shared_ptr<Texture> texture);
	};
}