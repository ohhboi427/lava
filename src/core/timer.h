#pragma once

#include <chrono>
#include <ratio>

namespace lava
{
	using period_nano = std::ratio<1, 1000000000>;
	using period_micro = std::ratio<1, 1000000>;
	using period_milli = std::ratio<1, 1000>;
	using period_sec = std::ratio<1, 1>;
	using period_min = std::ratio<60, 1>;
	using period_hour = std::ratio<3600, 1>;

	class timer
	{
	public:
		timer();
		timer(const timer&) = delete;
		timer(timer&&) noexcept = delete;
		~timer();

		timer& operator=(const timer&) = delete;
		timer& operator=(timer&&) noexcept = delete;

		void reset();
		void tick();

		template<typename TType = float, typename TPeriod = period_sec>
		TType elpased_time() const
		{
			return std::chrono::duration_cast<std::chrono::duration<TType, TPeriod>>(m_current - m_start).count();
		}

		template<typename TType = float, typename TPeriod = period_sec>
		TType delta_time() const
		{
			return std::chrono::duration_cast<std::chrono::duration<TType, TPeriod>>(m_current - m_last).count();
		}

	private:
		using clock = std::chrono::steady_clock;
		using time = clock::time_point;

		clock m_clock;
		time m_start;
		time m_current;
		time m_last;
	};
}
