#include "dhpch.h"

#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace DH {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			DH_CORE_ASSERT(false, "You Should Choose the Renderer Api First.");
			return nullptr;
		case RendererAPI::OpenGL:
			return  new OpenGLVertexBuffer(vertices, size);
		}


		DH_CORE_ASSERT(false, "Unknown Renderer Api.");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			DH_CORE_ASSERT(false, "You Should Choose the Renderer Api First.");
			return nullptr;
		case RendererAPI::OpenGL:
			return  new OpenGLIndexBuffer(indices, size);
		}


		DH_CORE_ASSERT(false, "Unknown Renderer Api.");
		return nullptr;
	}

}