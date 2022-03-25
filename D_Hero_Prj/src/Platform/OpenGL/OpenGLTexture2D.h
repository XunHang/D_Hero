#pragma once

#include "DHero/Core/Core.h"
#include "DHero/Renderer/Texture.h"
#include "stb_image.h"

namespace DH {

	class DH_API OpenGLTexture2D :public Texture2D {

	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;
		virtual void SetData(void* data, uint32_t size) override;
		virtual void Bind(uint32_t slot = 0) const override;

	private:
		unsigned int m_TextureID;
		int m_Width, m_Height;

	};
}