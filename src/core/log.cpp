#include "pch.h"
#include "log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace lava
{
	std::shared_ptr<spdlog::logger> log::detail::get_logger()
	{
		static std::shared_ptr<spdlog::logger> s_logger;
		if(!s_logger)
		{
			s_logger = spdlog::stdout_color_mt("lava");
			s_logger->set_pattern("%^%T [%l]: %v%$");
			s_logger->set_level(spdlog::level::trace);
			s_logger->flush_on(spdlog::level::warn);
		}

		return s_logger;
	}
}
