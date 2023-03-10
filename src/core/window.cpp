#include "pch.h"
#include "window.h"

#include <GLFW/glfw3.h>

namespace lava
{
	uint8_t window::s_window_count = 0u;

	window::window(int width, int height, const std::string& title)
		: m_width(width), m_height(height), m_title(title)
	{
		if(s_window_count++ == 0u)
		{
			glfwInit();

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef LAVA_DEBUG
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif // LAVA_DEBUG
		}

		m_handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

		glfwSetWindowUserPointer(m_handle, this);

		glfwSetWindowCloseCallback(m_handle, window::on_close_handler);
		glfwSetFramebufferSizeCallback(m_handle, window::on_resize_handler);
	}

	window::~window()
	{
		glfwDestroyWindow(m_handle);

		if(--s_window_count == 0u)
		{
			glfwTerminate();
		}
	}

	void window::on_close_handler(GLFWwindow* handle)
	{
		window& window = window_from_handle(handle);
		window.on_close_event();
	}

	void window::on_resize_handler(GLFWwindow* handle, int width, int height)
	{
		window& window = window_from_handle(handle);
		window.m_width = width;
		window.m_height = height;
		window.on_resize_event(window.m_width, window.m_height);
	}

	window& window_from_handle(GLFWwindow* handle)
	{
		return *((window*)glfwGetWindowUserPointer(handle));
	}
}
