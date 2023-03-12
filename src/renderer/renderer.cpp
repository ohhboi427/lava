#include "pch.h"
#include "renderer.h"

#include "shader_library.h"
#include "../core/logger.h"
#include "../core/window.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace lava
{
	renderer::renderer(window& window)
		: m_window(window)
	{
		glfwMakeContextCurrent(m_window);
		gladLoadGL((GLADloadfunc)glfwGetProcAddress);

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

		on_window_resize_callback(m_window.width(), m_window.height());
		m_window.on_resize_event += std::bind(&renderer::on_window_resize_callback, this, std::placeholders::_1, std::placeholders::_2);

#ifdef LAVA_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(renderer::opengl_debug_message_handler, nullptr);
#endif // LAVA_DEBUG

		shader_library::load_all("res/shaders");
	}

	renderer::~renderer()
	{
		shader_library::purge_cache();
	}

	void renderer::render_frame()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// TODO: Rendering

		glfwSwapBuffers(m_window);
	}

	void renderer::on_window_resize_callback(int width, int heigth)
	{
		glViewport(0, 0, width, heigth);
	}

	void renderer::opengl_debug_message_handler(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int32_t length, const char* message, const void* user_param)
	{
		std::string msg = std::regex_replace(std::string(message), std::regex("\n"), "");

		switch(severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			LAVA_LOGGER.error("OpenGL[{}]: {}", id, msg);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
		case GL_DEBUG_SEVERITY_LOW:
			LAVA_LOGGER.warning("OpenGL[{}]: {}", id, msg);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			LAVA_LOGGER.info("OpenGL[{}]: {}", id, msg);
			break;
		}
	}
}
