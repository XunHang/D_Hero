#include "dhpch.h"

#include "ShaderLibrary.h"


namespace DH {

	//void ShaderLibrary::Load(const std::string path) {
	//	std::shared_ptr<Shader> sp = Shader::Create(path);

	//	// 通过字串获取shader文件的名字
	//	size_t begin = path.find_last_of("\\/") + 1;
	//	size_t end = path.find_last_of(".");

	//	std::string shaderName = path.substr(begin, end - begin);

	//	m_Library[shaderName] = sp;
	//}

	//std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name) {
	//	DH_CORE_ASSERT(isContain(name), "Can't find shader {0}.", name);
	//	return m_Library[name];
	//}

	//bool ShaderLibrary::isContain(const std::string& name) {
	//	return m_Library.find(name) != m_Library.end();
	//}
	void ShaderLibrary::Load(const std::string& path)
	{
		std::shared_ptr<Shader> sp = Shader::Create(path);

		// get shader last name with out suffix as the shader name
		size_t end = path.find_last_of('.');
		size_t begin = path.find_last_of("\\/") + 1;

		std::string name = path.substr(begin, end - begin);

		m_Map[name] = sp;
		//m_Map.insert(name, sp);
	}

	std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& shaderName)
	{
		DH_CORE_ASSERT(Contains(shaderName), "Can't find shader:{0}", shaderName);

		return m_Map[shaderName];
	}

	bool ShaderLibrary::Contains(const std::string& shaderName)
	{
		return m_Map.find(shaderName) != m_Map.end();
	}
}