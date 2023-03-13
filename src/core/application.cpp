#include "pch.h"
#include "application.h"

#include "timer.h"
#include "window.h"
#include "../ecs/system_manager.h"
#include "../ecs/world.h"
#include "../renderer/renderer.h"

#include <GLFW/glfw3.h>

namespace lava
{
	application::application()
	{
		m_timer = new timer();

		m_window = new window(800, 600, "lava");
		m_window->on_close_event += [&] { m_running = false; };

		m_system_manager = new system_manager();

		m_world = new world();

		m_renderer = new renderer(*m_window);
	}

	application::~application()
	{
		delete m_renderer;
		delete m_world;
		delete m_system_manager;
		delete m_window;
		delete m_timer;
	}

	void application::run()
	{
		m_system_manager->start_all(*m_world);

		m_timer->reset();
		while(m_running)
		{
			glfwPollEvents();
			m_timer->tick();
			m_system_manager->update_all(*m_world, *m_timer);

			m_renderer->render_frame();
		}

		m_system_manager->stop_all(*m_world);
	}
}
