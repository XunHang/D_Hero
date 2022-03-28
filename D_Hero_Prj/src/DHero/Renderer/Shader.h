#pragma once

#include "DHero/Core/Core.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace DH {
	class DH_API Shader {
	public:
		~Shader() {};

		static std::shared_ptr<Shader> Create(const std::string& path);
		static std::shared_ptr<Shader> Create(const std::string& vSrc, const std::string& fSrc);

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void UploadUniformMat4(const std::string& uniformName, glm::mat4 matrix) = 0;
		virtual void UploadUniformVec4(const std::string& uniformName, glm::vec4 vec4) = 0;
		virtual void UploadUniformI1(const std::string& uniformName, int id) = 0;
	};
}