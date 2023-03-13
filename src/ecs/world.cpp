#include "pch.h"
#include "world.h"

#include "entity.h"

namespace lava
{
	world::world()
	{}

	world::~world()
	{}

	entity world::create_entity()
	{
		return entity(m_entities.create(), this);
	}

	void world::destroy_entity(entity& entity)
	{
		if(entity.m_world != this)
		{
			return;
		}

		m_entities.destroy(entity.m_handle);

		entity.m_handle = entt::null;
		entity.m_world = nullptr;
	}
}
