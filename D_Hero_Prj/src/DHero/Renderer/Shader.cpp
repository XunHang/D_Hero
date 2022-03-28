#include "dhpch.h"

#include "Shader.h"
#include "Renderer.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace DH {
	std::shared_ptr<Shader> Shader::Create(const std::string& path)	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::Type::None:
			DH_CORE_ASSERT(false, "You Should Choose the Renderer Api First.");
			return nullptr;
		case RendererAPI::Type::OpenGL:
			return  std::make_shared<OpenGLShader>(path);
		}
		DH_CORE_ASSERT(false, "Unknown Renderer Api.");
		return nullptr;
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& vSrc, const std::string& fSrc) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::Type::None:
			DH_CORE_ASSERT(false, "You Should Choose the Renderer Api First.");
			return nullptr;
		case RendererAPI::Type::OpenGL:
			return  std::make_shared<OpenGLShader>(vSrc, fSrc);
		}
		DH_CORE_ASSERT(false, "Unknown Renderer Api.");
		return nullptr;
	}
}