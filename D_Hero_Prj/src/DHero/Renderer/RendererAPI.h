#pragma once

#include "DHero/Core/Core.h"
#include "DHero/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace DH {
	// 定义虚基类，具体实现由具体平台决定
	class DH_API RendererAPI {

	public:
		enum class Type {
			None = 0, OpenGL = 1,
		};

	public:
		// 设定基本的渲染接口
		virtual void Init() const = 0;
		virtual void Clear() const = 0;
		virtual void ClearColor(const glm::vec4&) const = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>&) const = 0;

		inline static Type GetAPI() { return m_RendererAPI; }

	private:
		static Type m_RendererAPI;

	};

}