#include "pch.h"
#include "logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace lava
{
	logger* logger::s_main = nullptr;

	logger::logger(const std::string& name, const std::string& pattern)
	{
		m_logger = spdlog::stdout_color_mt(name);
		m_logger->set_pattern(pattern);
		m_logger->set_level(spdlog::level::trace);
		m_logger->flush_on(spdlog::level::warn);
	}

	logger* logger::create(const std::string& name, const std::string& pattern)
	{
		logger* newLogger = new logger(name, pattern);

		if(s_main == nullptr)
		{
			s_main = newLogger;
		}

		return newLogger;
	}

	logger& logger::main()
	{
		return *s_main;
	}
}
