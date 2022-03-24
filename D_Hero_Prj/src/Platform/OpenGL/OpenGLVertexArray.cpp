#include "dhpch.h"

#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace DH {
	OpenGLVertexArray::OpenGLVertexArray() {
		glGenVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray() {
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const {
		glBindVertexArray(m_RendererID);
	}
    
	void OpenGLVertexArray::UnBind() const {
		glBindVertexArray(0);
	}

	static GLenum ShaderDataTypeToOpenGL(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:
			return GL_FLOAT;
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return GL_INT;
		case ShaderDataType::Bool:
			return GL_BOOL;
		}

		DH_CORE_ASSERT(false, "Unknown Shader Data Type.");

		return 0;
	}

	void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer) {
		DH_CORE_ASSERT(vertexBuffer->GetLayout().GetCount(), "Emputy Layout in Vertex Buffer.");

		// 将 VBO 的数据放入 VAO 之前，需要先完成绑定
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		BufferLayout layout = vertexBuffer->GetLayout();
		int index = 0;
		for (const BufferElement& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				ShaderDataTypeCount(element.GetType()),
				ShaderDataTypeToOpenGL(element.GetType()),
				element.IsNormalized() ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(uint64_t)(element.GetOffset()));
			index++;
		}
		m_VertexBuffers.emplace_back(vertexBuffer);
	}

	void OpenGLVertexArray::AddIndexBuffer(std::shared_ptr<IndexBuffer>& indexBuffer) {
		// 将 VBO 的数据放入 VAO 之前，需要先完成绑定
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
	}

	const std::vector<std::shared_ptr<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffer() const {
		return m_VertexBuffers;
	}

	const std::shared_ptr<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const {
		return m_IndexBuffer;
	}
}