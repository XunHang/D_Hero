#include "dhpch.h"

#include "VertexArray.h"
#include "Renderer.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace DH {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::Type::None:
			DH_CORE_ASSERT(false, "You Should Choose the Renderer Api First.");
			return nullptr;
		case RendererAPI::Type::OpenGL:
			return  new OpenGLVertexArray();
		}


		DH_CORE_ASSERT(false, "Unknown Renderer Api.");
		return nullptr;
	}

}