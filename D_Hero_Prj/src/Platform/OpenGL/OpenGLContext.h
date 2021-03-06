#pragma once

#include "DHero/Core/Core.h"
#include "DHero/Core/Window.h"

#include "DHero/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace DH {

	class DH_API OpenGLContext :public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;

	};

}