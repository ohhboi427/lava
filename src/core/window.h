#pragma once

#include "../utility/event.h"

#include <string>
#include <string_view>
#include <cstdint>

struct GLFWwindow;

namespace lava
{
	class window
	{
	public:
		event<> on_close_event;
		event<int, int> on_resize_event;

		window(int width, int height, const std::string& title);
		window(const window&) = delete;
		window(window&&) noexcept = delete;
		~window();

		window& operator=(const window&) = delete;
		window& operator=(window&&) noexcept = delete;
		
		operator GLFWwindow* () const { return m_handle; }

		int width() const { return m_width; }
		int height() const { return m_height; }
		std::string_view title() const { return m_title; }

	private:
		static uint8_t s_window_count;

		GLFWwindow* m_handle;
		int m_width;
		int m_height;
		std::string m_title;

		static void on_close_handler(GLFWwindow* handle);
		static void on_resize_handler(GLFWwindow* handle, int width, int height);
	};

	window& window_from_handle(GLFWwindow* handle);
}
