#include "pch.h"
#include "application.h"

#include "logger.h"
#include "window.h"
#include "../renderer/renderer.h"

#include <GLFW/glfw3.h>

namespace lava
{
	application::application()
	{
		m_logger = logger::create("lava", "%^%T [%l]: %v%$");

		m_window = new window(800, 600, "lava");
		m_window->on_close_event += [&] { m_running = false; };

		m_renderer = new renderer(*m_window);
	}

	application::~application()
	{
		delete m_renderer;

		delete m_window;

		delete m_logger;
	}

	void application::run()
	{
		while(m_running)
		{
			glfwPollEvents();

			m_renderer->render_frame();
		}
	}
}
