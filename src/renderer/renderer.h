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

		static void opengl_debug_message_handler(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int32_t length, const char* message, const void* user_param);

		void on_window_resize_callback(int width, int heigth);
	};
}
