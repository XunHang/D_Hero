#pragma once

#include "DHero/Core/Core.h"
#include "DHero/Renderer/Buffer.h"


namespace DH {

	class DH_API VertexArray {
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		static VertexArray* Create();

		virtual void AddVertexBuffer(std::shared_ptr<VertexBuffer>&) = 0;
		virtual void AddIndexBuffer(std::shared_ptr<IndexBuffer>&) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffer() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

	};

}