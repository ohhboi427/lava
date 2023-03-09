#include "pch.h"
#include "application.h"

#include "logger.h"
#include "window.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace lava
{
	application::application()
	{
		m_logger = logger::create("lava", "%^%T [%l]: %v%$");

		m_window = new window(800, 600, "lava");
		m_window->on_close_event += [&] { m_running = false; };
	}

	application::~application()
	{
		delete m_window;

		delete m_logger;
	}

	void application::run()
	{
		glfwMakeContextCurrent(*m_window);
		gladLoadGL((GLADloadfunc)glfwGetProcAddress);

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

		while(m_running)
		{
			glfwPollEvents();

			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(*m_window);
		}
	}
}
