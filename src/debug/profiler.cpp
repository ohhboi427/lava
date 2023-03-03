#include "pch.h"
#include "profiler.h"

#include "../core/logger.h"
#include "../core/timer.h"

namespace lava
{
	profiler::profiler(const std::string& name)
		: m_name(name)
	{
		m_timer = new timer();
		m_timer->reset();
	}

	profiler::~profiler()
	{
		m_timer->tick();
		LAVA_LOGGER.debug("{} took {}ns.", m_name, m_timer->elpased_time<uint64_t, period_nano>());

		delete m_timer;
	}
}
