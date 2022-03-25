#include "dhpch.h"

#include "Texture.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace DH {

	Texture2D* Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::Type::None:
			DH_CORE_ASSERT(false, "Please Choose The Renderer API.");
		case RendererAPI::Type::OpenGL:
			return new OpenGLTexture2D(path);
		default:
			break;
		}
	}
	Texture2D* Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::Type::None:
			DH_CORE_ASSERT(false, "Please Choose The Renderer API.");
		case RendererAPI::Type::OpenGL:
			return new OpenGLTexture2D(width, height);
		default:
			break;
		}
	}

}