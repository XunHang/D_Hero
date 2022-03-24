#pragma once
#include "DHero/Core/Core.h"
#include "DHero/Renderer/RendererAPI.h"

namespace DH {

	class DH_API OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void Init() const override;
		virtual void Clear() const override;
		virtual void ClearColor(const glm::vec4&) const override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>&) const override;

	private:
	};

}
