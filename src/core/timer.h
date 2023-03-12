#pragma once

#include <ratio>
#include <chrono>

namespace lava
{
	using nanosecond_t = std::ratio<1, 1000000000>;
	using microsecond_t = std::ratio<1, 1000000>;
	using millisecond_t = std::ratio<1, 1000>;
	using second_t = std::ratio<1, 1>;
	using minute_t = std::ratio<60, 1>;
	using hour_t = std::ratio<3600, 1>;

	class timer
	{
	public:
		timer() = default;
		timer(const timer&) = delete;
		timer(timer&&) noexcept = delete;

		timer& operator=(const timer&) = delete;
		timer& operator=(timer&&) noexcept = delete;

		void reset();
		void tick();

		template<typename TPeriod = second_t, typename TType = float>
		TType elpased_time() const
		{
			return std::chrono::duration_cast<std::chrono::duration<TType, TPeriod>>(m_current - m_start).count();
		}

		template<typename TPeriod = second_t, typename TType = float>
		TType delta_time() const
		{
			return std::chrono::duration_cast<std::chrono::duration<TType, TPeriod>>(m_current - m_last).count();
		}

	private:
		using clock_t = std::chrono::steady_clock;
		using time_t = clock_t::time_point;

		clock_t m_clock;
		time_t m_start;
		time_t m_current;
		time_t m_last;
	};
}
