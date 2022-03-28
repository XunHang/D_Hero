#pragma once

#include "DHero/Core/Core.h"

#include "Shader.h"


namespace DH {

	//class DH_API ShaderLibrary {

	//public:
	//	void Load(const std::string path);
	//	std::shared_ptr<Shader> Get(const std::string& name);
	//	bool isContain(const std::string& name);

	//private:
	//	std::unordered_map<std::string, std::shared_ptr<Shader>> m_Library;

	//};
	class ShaderLibrary
	{
	public:
		void Load(const std::string& path);
		std::shared_ptr<Shader> Get(const std::string& shaderName);
		bool Contains(const std::string& shaderName);

	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_Map;
	};
}