#include "pch.h"
#include "entity.h"

namespace lava
{
	entity::entity()
		: m_handle(entt::null), m_world(nullptr)
	{}

	entity::entity(entt::entity handle, world* world)
		: m_handle(handle), m_world(world)
	{}

	entity::entity(const entity& other)
		: m_handle(other.m_handle), m_world(other.m_world)
	{}

	entity::entity(entity&& other) noexcept
		: m_handle(other.m_handle), m_world(other.m_world)
	{
		other.m_handle = entt::null;
		other.m_world = nullptr;
	}

	entity& entity::operator=(const entity& rhs)
	{
		m_handle = rhs.m_handle;
		m_world = rhs.m_world;

		return *this;
	}

	entity& entity::operator=(entity&& rhs) noexcept
	{
		m_handle = rhs.m_handle;
		m_world = rhs.m_world;

		rhs.m_handle = entt::null;
		rhs.m_world = nullptr;

		return *this;
	}
}
