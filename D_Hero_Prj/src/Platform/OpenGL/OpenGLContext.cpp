#include "dhpch.h"

#include "OpenGLContext.h"
#include <glad/glad.h>

namespace DH {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle) {
		DH_CORE_ASSERT(windowHandle, "Window Handle is Null!");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		DH_ASSERT(status, "Failed to load GLAD");

		DH_CORE_INFO("OpenGL Info:");
		DH_CORE_INFO("\tVendor: {0}", glGetString(GL_VENDOR));
		DH_CORE_INFO("\tRenderer: {0}", glGetString(GL_RENDERER));
		DH_CORE_INFO("\tVersion: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() {

		glfwSwapBuffers(m_WindowHandle);
	}
}