#pragma once

namespace lava
{
	class logger;
	class window;

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
		window* m_window;
	};
}
