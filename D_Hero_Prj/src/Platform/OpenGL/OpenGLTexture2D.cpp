#include "dhpch.h"

#include "OpenGLTexture2D.h"
#include <glad/glad.h>


namespace DH {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) {
		stbi_set_flip_vertically_on_load(true);

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int channel;
		unsigned char* data = stbi_load(path.c_str(), &m_Width, &m_Height, &channel, 0);
		if (!data) {
			data = new unsigned char[2 * 2 * 4]{
			0xFF, 0x00, 0xFF,0xFF,  0xFF, 0x00, 0xFF,0xFF,
			0xFF, 0x00, 0xFF,0xFF,  0xFF, 0x00, 0xFF,0xFF,
			};
			m_Width = 2;
			m_Height = 2;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			DH_CORE_ERROR("Load Texture File Failed.");
			return;
		}

		//DH_CORE_ASSERT(data, "Failed to load texture.");

		DH_CORE_INFO("\nTexture w:{0}, h:{1}, c:{2}", m_Width, m_Height, channel);
		switch (channel)
		{
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			break;
		case 4:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			break;
		default:
			DH_CORE_ASSERT(false, "Unsupported texture format!");
			break;
		}

		stbi_image_free(data);
	}

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		:m_Width(width), m_Height(height){
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}
	
	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &m_TextureID);
	}

	uint32_t OpenGLTexture2D::GetWidth() const {
		return m_Width;
	}

	uint32_t OpenGLTexture2D::GetHeight() const {
		return m_Height;
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const {
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size) {
		// bpp: bytes per pixel
		uint32_t bpp = 4;// 默认是用RGBA的格式
		DH_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	}
}
