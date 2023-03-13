#pragma once

namespace lava
{
	class timer;
	class window;
	class system_manager;
	class world;
	class renderer;

	class application
	{
	public:
		application();
		application(const application&) = delete;
		application(application&&) noexcept = delete;
		~application();

		application& operator=(const application&) = delete;
		application& operator=(application&&) noexcept = delete;

		void run();

	private:
		bool m_running = true;
		timer* m_timer;
		window* m_window;
		system_manager* m_system_manager;
		world* m_world;
		renderer* m_renderer;
	};
}
