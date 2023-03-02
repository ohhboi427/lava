#pragma once

namespace lava
{
	class logger;

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
		logger* m_logger;
	};
}
