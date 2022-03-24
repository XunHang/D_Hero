#pragma once

#include "DHero/Core/Core.h"

namespace DH {
	enum class ShaderDataType {
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:
			return 4;
		case ShaderDataType::Float2:
			return 4 * 2;
		case ShaderDataType::Float3:
			return 4 * 3;
		case ShaderDataType::Float4:
			return 4 * 4;
		case ShaderDataType::Mat3:
			return 4 * 3 * 3;
		case ShaderDataType::Mat4:
			return 4 * 4 * 4;
		case ShaderDataType::Int:
			return 4;
		case ShaderDataType::Int2:
			return 4 * 2;
		case ShaderDataType::Int3:
			return 4 * 3;
		case ShaderDataType::Int4:
			return 4 * 4;
		case ShaderDataType::Bool:
			return 1;
		}

		DH_CORE_ASSERT(false, "Unknown Shader Data Type.");

		return 0;
	}

	static uint32_t ShaderDataTypeCount(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:
			return 1;
		case ShaderDataType::Float2:
			return 1 * 2;
		case ShaderDataType::Float3:
			return 1 * 3;
		case ShaderDataType::Float4:
			return 1 * 4;
		case ShaderDataType::Mat3:
			return 1 * 3 * 3;
		case ShaderDataType::Mat4:
			return 1 * 4 * 4;
		case ShaderDataType::Int:
			return 1;
		case ShaderDataType::Int2:
			return 1 * 2;
		case ShaderDataType::Int3:
			return 1 * 3;
		case ShaderDataType::Int4:
			return 1 * 4;
		case ShaderDataType::Bool:
			return 1;
		}

		DH_CORE_ASSERT(false, "Unknown Shader Data Type.");

		return 0;
	}

	class DH_API BufferElement {
	public:
		BufferElement(ShaderDataType type, const std::string& name, bool isNormalized = false)
			:m_Name(name), m_Type(type), m_Size(ShaderDataTypeSize(type)), m_Offset(0), m_IsNormalized(isNormalized) {
		}
		void SetOffet(uint32_t offset) { m_Offset = offset; }

		uint32_t GetSize() const{ return m_Size; }
		uint32_t GetOffset() const { return m_Offset; }
		ShaderDataType GetType() const { return m_Type; }
		bool IsNormalized() const { return m_IsNormalized; }

	private:
		std::string m_Name;
		ShaderDataType m_Type;
		uint32_t m_Size;
		uint32_t m_Offset;
		bool m_IsNormalized;
	};

	class DH_API BufferLayout {
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:m_Elements(elements) {
			CalculateOffsetAndStride();
		}

		uint32_t GetStride() const { return m_Stride; }
		size_t GetCount() const { return m_Elements.size(); }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

	private:
		void CalculateOffsetAndStride();

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride;

	};

	class DH_API VertexBuffer {
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual BufferLayout& GetLayout() = 0;
		virtual void SetLayout(const BufferLayout& ) = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class DH_API IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};


}