#pragma once

#include "world.h"

#include <utility>

#include <entt/entt.hpp>

namespace lava
{
	class entity
	{
		friend class world;

	public:
		entity() = default;
		entity(entt::entity handle, world* world);
		entity(const entity& other);
		entity(entity&& other) noexcept;

		entity& operator=(const entity& rhs);
		entity& operator=(entity&& rhs) noexcept;

		template<typename T, typename... Args>
		T& add_component(Args&&... args)
		{
			return m_world->m_entities.emplace<T>(m_handle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& get_component()
		{
			return m_world->m_entities.get<T>(m_handle);
		}

		template<typename T>
		void remove_component()
		{
			m_world->m_entities.remove<T>(m_handle);
		}

		template<typename T>
		bool has_component() const
		{
			return m_world->m_entities.all_of<T>(m_handle);
		}

	private:
		entt::entity m_handle = entt::null;
		world* m_world = nullptr;
	};
}
