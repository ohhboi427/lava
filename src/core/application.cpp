#include "pch.h"
#include "application.h"

#include "logger.h"
#include "timer.h"
#include "window.h"
#include "../renderer/renderer.h"
#include "../renderer/shader.h"
#include "../renderer/shader_library.h"
#include "../system/system.h"
#include "../system/system_manager.h"

#include <GLFW/glfw3.h>

namespace lava
{
	application::application()
	{
		m_logger = logger::create("lava", "%^%T [%l]: %v%$");

		m_timer = new timer();

		m_window = new window(800, 600, "lava");
		m_window->on_close_event += [&] { m_running = false; };

		m_renderer = new renderer(*m_window);

		m_system_manager = new system_manager();
	}

	application::~application()
	{
		delete m_system_manager;
		delete m_renderer;
		delete m_window;
		delete m_timer;
		delete m_logger;
	}

	void application::run()
	{
		m_system_manager->start_all();

		m_timer->reset();
		while(m_running)
		{
			glfwPollEvents();
			m_timer->tick();
			m_system_manager->update_all(*m_timer);

			m_renderer->render_frame();
		}

		m_system_manager->stop_all();
	}
}
