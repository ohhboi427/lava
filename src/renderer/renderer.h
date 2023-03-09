#pragma once

namespace lava
{
	class window;

	class renderer
	{
	public:
		renderer(window& window);
		renderer(const renderer&) = delete;
		renderer(renderer&&) noexcept = delete;
		~renderer();

		renderer& operator=(const renderer&) = delete;
		renderer& operator=(renderer&&) noexcept = delete;

		void render_frame();

	private:
		window& m_window;

		void on_window_resize_callback(int width, int heigth);
	};
}
