#include "gepch.h"
#include "OpenGLContext.h"

#include <GLfW/glfw3.h>
#include <glad/glad.h>

namespace GameEngine
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		GE_CORE_ASSERT(windowHandle, "Window handle is null.")
	}

	void OpenGLContext::Init()
	{
		GE_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GE_CORE_ASSERT(status, "Failed to init glad.");

		GE_CORE_INFO("OpenGL Renderer: {0}", (const char*)glGetString(GL_RENDERER));
	}

	void OpenGLContext::SwapBuffers()
	{
		GE_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}