#include "pch.h"
#include "GraphicsContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace myo {

	GraphicsContext::GraphicsContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		CORE_ASSERT(m_WindowHandle, "Window Handle is null!")
	}

	void GraphicsContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CORE_ASSERT(status, "Failed to initialize Glad!");

		CORE_INFO("OpenGL Info:");
		CORE_INFO("    Vendor: {0}", glGetString(GL_VENDOR));
		CORE_INFO("    Renderer: {0}", glGetString(GL_RENDERER));
		CORE_INFO("    Version: {0}", glGetString(GL_VERSION));

#ifdef ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "This rendering engine requires at least OpenGL version 4.5!");
#endif
	}

	void GraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}