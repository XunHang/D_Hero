#pragma once

#include "DHero/Core.h"

namespace DH {
	enum class RendererAPI {
		None = 0, OpenGL = 1,
	};

	class DH_API Renderer {
	public:
		static inline RendererAPI GetAPI() { return m_RendererAPI; }
		//static inline void SetAPI(RendererAPI api) { m_RendererAPI = api; }

	protected:

	private:
		static RendererAPI m_RendererAPI;
	};
}
