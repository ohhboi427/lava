#pragma once

namespace lava
{
	class logger;
	class timer;
	class window;
	class renderer;
	class system_manager;

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
		logger* m_logger;
		timer* m_timer;
		window* m_window;
		renderer* m_renderer;
		system_manager* m_system_manager;
	};
}
