#include "dhpch.h"

#include "Shader.h"

#include <glad/glad.h>

namespace DH {
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
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

	Shader::~Shader() {
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const {
		glUseProgram(m_RendererID);
	}

	void Shader::UnBind() const {
		glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& paramName, const glm::mat4& matrix) {
		int location = glGetUniformLocation(m_RendererID, paramName.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

}