#include "pch.h"
#include "timer.h"

namespace lava
{
	void timer::reset()
	{
		m_start = m_clock.now();
		m_current = m_start;
		m_last = m_start;
	}

	void timer::tick()
	{
		m_last = m_current;
		m_current = m_clock.now();
	}
}
