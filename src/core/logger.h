#pragma once

#include <spdlog/spdlog.h>

#include <memory>
#include <utility>
#include <string>
#include <string_view>

namespace lava
{
	class logger
	{
	public:
		logger(const logger&) = delete;
		logger(logger&&) noexcept = delete;

		logger& operator=(const logger&) = delete;
		logger& operator=(logger&&) noexcept = delete;

		static logger* create(const std::string& name, const std::string& pattern);
		static logger& main();

		template<typename... Args>
		void trace(std::string_view fmt, Args&&... args)
		{
			m_logger->trace(fmt, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void debug(std::string_view fmt, Args&&... args)
		{
			m_logger->debug(fmt, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void info(std::string_view fmt, Args&&... args)
		{
			m_logger->info(fmt, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void warning(std::string_view fmt, Args&&... args)
		{
			m_logger->warn(fmt, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void error(std::string_view fmt, Args&&... args)
		{
			m_logger->error(fmt, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void critical(std::string_view fmt, Args&&... args)
		{
			m_logger->critical(fmt, std::forward<Args>(args)...);
		}

	private:
		static logger* s_main;
		
		std::shared_ptr<spdlog::logger> m_logger;

		logger(const std::string& name, const std::string& pattern);
	};
}

#define LAVA_LOGGER (::lava::logger::main())
