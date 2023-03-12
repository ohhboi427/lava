#include "pch.h"
#include "system_manager.h"

#include "system.h"
#include "../core/timer.h"

namespace lava
{
	system_manager::~system_manager()
	{
		for(const auto& system : m_systems)
		{
			delete system;
		}
	}

	void system_manager::start_all()
	{
		for(auto& system : m_systems)
		{
			system->on_start();
		}
	}

	void system_manager::update_all(const timer& timer)
	{
		for(auto& system : m_systems)
		{
			system->on_update(timer);
		}
	}

	void system_manager::stop_all()
	{
		for(auto& system : m_systems)
		{
			system->on_stop();
		}
	}
}
