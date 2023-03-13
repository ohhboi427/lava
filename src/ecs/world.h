#pragma once

#include <entt/entt.hpp>

namespace lava
{
	class entity;

	class world
	{
		friend class entity;

	public:
		world();
		world(const world&) = delete;
		world(world&&) noexcept = delete;
		~world();

		world& operator=(const world&) = delete;
		world& operator=(world&&) noexcept = delete;

		entity create_entity();
		void destroy_entity(entity& entity);

		template<typename... Args>
		auto view()
		{
			return m_entities.view<Args...>();
		}

		template<typename... Args>
		auto view() const
		{
			return m_entities.view<Args...>();
		}

		template<typename... Args>
		auto group()
		{
			return m_entities.group<Args...>();
		}

	private:
		entt::registry m_entities;
	};
}
