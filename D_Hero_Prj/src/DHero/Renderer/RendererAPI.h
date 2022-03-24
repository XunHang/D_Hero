#pragma once

#include "DHero/Core/Core.h"
#include "DHero/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace DH {
	// ��������࣬����ʵ���ɾ���ƽ̨����
	class DH_API RendererAPI {

	public:
		enum class Type {
			None = 0, OpenGL = 1,
		};

	public:
		// �趨��������Ⱦ�ӿ�
		virtual void Init() const = 0;
		virtual void Clear() const = 0;
		virtual void ClearColor(const glm::vec4&) const = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>&) const = 0;

		inline static Type GetAPI() { return m_RendererAPI; }

	private:
		static Type m_RendererAPI;

	};

}