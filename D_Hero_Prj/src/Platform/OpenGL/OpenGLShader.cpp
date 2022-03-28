#include "dhpch.h"

#include "OpenGLShader.h"

namespace DH {
	unsigned int OpenGLShader::StringToGLShaderType(const std::string& name) {
		DH_CORE_TRACE("Shader Type: {0}", name);
		if (name == "vertex")	return GL_VERTEX_SHADER;
		if (name == "fragment") return GL_FRAGMENT_SHADER;
		if (name == "geometry")	return GL_GEOMETRY_SHADER;
		//if (name == "vertex")	return GL_COMPUTE_SHADER;

		DH_CORE_ASSERT(false, "Uknown Shader Type, please check your shader.");
		return -1;
	}

	void OpenGLShader::SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
	{
		std::string::size_type pos1, pos2;
		pos2 = s.find(c);
		pos1 = 0;
		while (std::string::npos != pos2)
		{
			v.push_back(s.substr(pos1, pos2 - pos1));

			pos1 = pos2 + c.size();
			pos2 = s.find(c, pos1);
		}
		if (pos1 != s.length())
			v.push_back(s.substr(pos1));
	}

	OpenGLShader::OpenGLShader(const std::string& path) {
		std::ifstream input(path);

		DH_CORE_ASSERT(input.good(), "Can't open {0}", path);
		// 创建一个字典对应各个shader的ID与程序
		std::unordered_map<GLuint, std::string> shaders;

		std::string line;
		while (getline(input, line)) {
			GLuint shaderID;
			if (line.find("#type") != std::string::npos) {
				int split = line.find_first_of(' ') + 1;
				GLuint shaderType = StringToGLShaderType(line.substr(split, line.size() - split));
				shaderID = glCreateShader(shaderType);
				shaders[shaderID] = "";
			}
			else {
				shaders[shaderID] += line;
				shaders[shaderID] += "\n";
			}
		}
		input.close();

		GLint program = glCreateProgram();;
		GLint _status = 0;
		for (auto it : shaders) {
			DH_CORE_TRACE("Shader Type: {0}", it.first);
			DH_CORE_TRACE("Shader Content:");
			DH_CORE_TRACE("{0}", it.second);
			const GLchar* source = (const GLchar*)(it.second).c_str();
			glShaderSource(it.first, 1, &source, nullptr);
			glCompileShader(it.first);
			glGetShaderiv(it.first, GL_COMPILE_STATUS, &_status);
			if (_status == GL_FALSE) {
				GLint maxLength = 0;
				glGetShaderiv(it.first, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(it.first, maxLength, &maxLength, &infoLog[0]);
				glDeleteShader(it.first);
				DH_CORE_ERROR("Shader Compiled Error: {0}", infoLog.data());
				DH_CORE_ASSERT(_status, "Shader Compiled Error.");
			}
			glAttachShader(program, it.first);
		}
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &_status);
		if (_status == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			glDeleteProgram(program);
			for (auto it : shaders) {
				glDetachShader(program, it.first);
			}
			DH_CORE_ERROR("Shaders Linke Program Error: {0}", infoLog.data());
			DH_CORE_ASSERT(_status, "Linke Program Error.");
		}
		for (auto it : shaders) {
			glDetachShader(program, it.first);
		}
		m_RendererID = program;
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc) {
		// Compiled Vertex Shader
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const GLchar* source = (const GLchar*)vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, nullptr);
		glCompileShader(vertexShader);
		GLint _status = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &_status);
		if (_status == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			glDeleteShader(vertexShader);
			DH_CORE_ERROR("Vertex Shader Compiled Error: {0}", infoLog.data());
			DH_CORE_ASSERT(_status, "Shader Compiled Error.");
		}

		// Compiled Fragment Shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		source = (const GLchar*)fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, nullptr);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &_status);
		if (_status == GL_FALSE) {
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
			glDeleteShader(fragmentShader);
			DH_CORE_ERROR("Fragment Shader Compiled Error: {0}", infoLog.data());
			DH_CORE_ASSERT(_status, "Shader Compiled Error.");
		}

		// Link Shaders To Program
		GLint program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &_status);
		if (_status == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			glDeleteProgram(program);
			glDetachShader(program, vertexShader);
			glDetachShader(program, fragmentShader);
			DH_CORE_ERROR("Shaders Linke Program Error: {0}", infoLog.data());
			DH_CORE_ASSERT(_status, "Linke Program Error.");
		}

		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);

		m_RendererID = program;
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind() const {
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformMat4(const std::string& uniformName, glm::mat4 matrix) {
		int location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformVec4(const std::string& uniformName, glm::vec4 vec4) {
		int location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform4fv(location, 1, glm::value_ptr(vec4));
	}

	void OpenGLShader::UploadUniformI1(const std::string& uniformName, int value) {
		int location = glGetUniformLocation(m_RendererID, uniformName.c_str());
		glUniform1i(location, value);
	}



}