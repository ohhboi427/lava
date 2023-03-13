#pragma once

#include "../utility/concepts.h"

#include <vector>

namespace lava
{
	class system;
	class timer;

	class system_manager
	{
	public:
		system_manager() = default;
		system_manager(const system_manager&) = delete;
		system_manager(system_manager&&) noexcept = delete;
		~system_manager();

		system_manager& operator=(const system_manager&) = delete;
		system_manager& operator=(system_manager&&) noexcept = delete;

		template<typename... Args>
		requires(is_base_of_n_v<system, Args...>)
		void create_systems()
		{
			m_systems = { create_system<Args>()... };
		}

		void start_all();
		void update_all(const timer& timer);
		void stop_all();

	private:
		std::vector<system*> m_systems;

		template<typename T>
		requires(std::is_base_of_v<system, T>)
		T* create_system()
		{
			return new T();
		}
	};
}
