#pragma once
#include "DHero/Core/Core.h"
#include "DHero/Renderer/Shader.h"

#include <glad/glad.h>

namespace DH {

	class DH_API OpenGLShader :public Shader {
	public:
		OpenGLShader(const std::string& path);
		OpenGLShader(const std::string& vSrc, const std::string& fSrc);
		~OpenGLShader();

		void Bind() const;
		void UnBind() const;

		void UploadUniformMat4(const std::string& uniformName, glm::mat4 matrix);
		void UploadUniformVec4(const std::string& uniformName, glm::vec4 vec4);
		void UploadUniformI1(const std::string& uniformName, int id);

	private:
		GLint m_RendererID;

	private:
		unsigned int StringToGLShaderType(const std::string& name);
		void OpenGLShader::SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c);
	};

}