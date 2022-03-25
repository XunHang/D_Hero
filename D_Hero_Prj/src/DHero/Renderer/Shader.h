#pragma once

#include "DHero/Core/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace DH {
	class DH_API Shader {
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void UnBind() const;

		void UploadUniform1i(const std::string& paramName, const int& value);
		void UploadUniformMat4(const std::string& param, const glm::mat4&);

	protected:
	
	private:
		uint32_t m_RendererID;	
	};
}