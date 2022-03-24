#pragma once

#include "DHero/Core/Core.h"
#include "DHero/Renderer/Buffer.h"
#include "DHero/Renderer/VertexArray.h"


namespace DH {

	class DH_API OpenGLVertexArray :public VertexArray {
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>&) override;
		virtual void AddIndexBuffer(std::shared_ptr<IndexBuffer>&) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const  override;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const  override;

	private:
		uint32_t m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

	};

}