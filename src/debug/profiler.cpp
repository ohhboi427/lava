#include "pch.h"
#include "profiler.h"

#include "../core/log.h"
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
		log::debug("{} took {}ns.", m_name, m_timer->elpased_time<nanosecond_t, uint64_t>());

		delete m_timer;
	}
}
