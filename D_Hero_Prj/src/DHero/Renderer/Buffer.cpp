#include "dhpch.h"

#include "Buffer.h"
#include "Renderer.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace DH {

	// 依据参数类型，计算步长
	void BufferLayout::CalculateOffsetAndStride() {
		m_Stride = 0;
		for (auto& element : m_Elements) {
			element.SetOffet(m_Stride);
			m_Stride += element.GetSize();
		}
	}

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::Type::None:
			DH_CORE_ASSERT(false, "You Should Choose the Renderer Api First.");
			return nullptr;
		case RendererAPI::Type::OpenGL:
			return  new OpenGLVertexBuffer(vertices, size);
		}


		DH_CORE_ASSERT(false, "Unknown Renderer Api.");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::Type::None:
			DH_CORE_ASSERT(false, "You Should Choose the Renderer Api First.");
			return nullptr;
		case RendererAPI::Type::OpenGL:
			return  new OpenGLIndexBuffer(indices, size);
		}


		DH_CORE_ASSERT(false, "Unknown Renderer Api.");
		return nullptr;
	}

}