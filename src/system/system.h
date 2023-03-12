#pragma once

namespace lava
{
	class timer;

	class system
	{
	public:
		system(const system&) = delete;
		system(system&&) noexcept = delete;
		virtual ~system() = default;

		system& operator=(const system&) = delete;
		system& operator=(system&&) noexcept = delete;

		virtual void on_start() {}
		virtual void on_update(const timer& timer) {}
		virtual void on_stop() {}

	protected:
		system() = default;
	};
}
