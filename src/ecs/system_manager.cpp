#include "pch.h"
#include "system_manager.h"

#include "system.h"
#include "world.h"
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

	void system_manager::start_all(world& world)
	{
		for(auto& system : m_systems)
		{
			system->on_start(world);
		}
	}

	void system_manager::update_all(world& world, const timer& timer)
	{
		for(auto& system : m_systems)
		{
			system->on_update(world, timer);
		}
	}

	void system_manager::stop_all(world& world)
	{
		for(auto& system : m_systems)
		{
			system->on_stop(world);
		}
	}
}
