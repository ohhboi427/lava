#pragma once

#include <chrono>
#include <ratio>

namespace lava
{
	using period_nano_t = std::ratio<1, 1000000000>;
	using period_micro_t = std::ratio<1, 1000000>;
	using period_milli_t = std::ratio<1, 1000>;
	using period_sec_t = std::ratio<1, 1>;
	using period_min_t = std::ratio<60, 1>;
	using period_hour_t = std::ratio<3600, 1>;

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

		template<typename TType = float, typename TPeriod = period_sec_t>
		TType elpased_time() const
		{
			return std::chrono::duration_cast<std::chrono::duration<TType, TPeriod>>(m_current - m_start).count();
		}

		template<typename TType = float, typename TPeriod = period_sec_t>
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
