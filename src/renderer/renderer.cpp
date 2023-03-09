#include "pch.h"
#include "renderer.h"

#include "../core/window.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace lava
{
	renderer::renderer(window& window)
		: m_window(window)
	{
		glfwMakeContextCurrent(m_window);
		gladLoadGL((GLADloadfunc)glfwGetProcAddress);

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

		on_window_resize_callback(m_window.width(), m_window.height());
		m_window.on_resize_event += std::bind(&renderer::on_window_resize_callback, this, std::placeholders::_1, std::placeholders::_2);
	}

	renderer::~renderer()
	{}

	void renderer::render_frame()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// TODO: Rendering

		glfwSwapBuffers(m_window);
	}

	void renderer::on_window_resize_callback(int width, int heigth)
	{
		glViewport(0, 0, width, heigth);
	}
}
