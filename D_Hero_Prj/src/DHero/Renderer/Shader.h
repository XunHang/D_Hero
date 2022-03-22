#pragma once

#include "DHero/Core.h"


namespace DH {
	class DH_API Shader {
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void UnBind() const;

	protected:
	
	private:
		uint32_t m_RendererID;	
	};
}