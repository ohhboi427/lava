#pragma once

#include <string>

namespace lava
{
	class timer;

	class profiler
	{
	public:
		profiler(const std::string& name);
		profiler(const profiler&) = delete;
		profiler(profiler&&) noexcept = delete;
		~profiler();

		profiler& operator=(const profiler&) = delete;
		profiler& operator=(profiler&&) noexcept = delete;

	private:
		timer* m_timer;
		std::string m_name;
	};
}

#ifdef LAVA_DEBUG
#  define LAVA_PROFILE_FUNCTION() ::lava::profiler profiler(__FUNCTION__)
#else
#  define LAVA_PROFILE_FUNCTION()
#endif // LAVA_DEBUG	
