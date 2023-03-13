#pragma once

#include <spdlog/spdlog.h>

#include <memory>
#include <utility>
#include <string>
#include <string_view>

namespace lava
{
	namespace log
	{
		namespace detail
		{
			std::shared_ptr<spdlog::logger> get_logger();
		}

		template<typename... Args>
		void trace(std::string_view fmt, Args&&... args)
		{
			detail::get_logger()->trace(fmt, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void debug(std::string_view fmt, Args&&... args)
		{
			detail::get_logger()->debug(fmt, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void info(std::string_view fmt, Args&&... args)
		{
			detail::get_logger()->info(fmt, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void warning(std::string_view fmt, Args&&... args)
		{
			detail::get_logger()->warn(fmt, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void error(std::string_view fmt, Args&&... args)
		{
			detail::get_logger()->error(fmt, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void critical(std::string_view fmt, Args&&... args)
		{
			detail::get_logger()->critical(fmt, std::forward<Args>(args)...);
		}
	};
}
