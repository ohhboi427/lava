#pragma once

#include <type_traits>
#include <vector>

namespace lava
{
	class system;
	class timer;

	template<typename T>
	concept system_base = (std::is_base_of<system, T>::value);

	template<typename... Args>
	concept system_base_n = (system_base<Args> && ...);

	class system_manager
	{
	public:
		system_manager() = default;
		system_manager(const system_manager&) = delete;
		system_manager(system_manager&&) noexcept = delete;
		~system_manager();

		template<typename... Args>
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
		T* create_system()
		{
			return new T();
		}
	};
}
