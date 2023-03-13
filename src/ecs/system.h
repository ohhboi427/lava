#pragma once

namespace lava
{
	class world;
	class timer;

	class system
	{
	public:
		system(const system&) = delete;
		system(system&&) noexcept = delete;
		virtual ~system() = default;

		system& operator=(const system&) = delete;
		system& operator=(system&&) noexcept = delete;

		virtual void on_start(world& world) {}
		virtual void on_update(world& world, const timer& timer) {}
		virtual void on_stop(world& world) {}

	protected:
		system() = default;
	};
}
