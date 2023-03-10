#include "pch.h"
#include "renderer.h"

#include "mesh.h"
#include "shader.h"
#include "../core/log.h"
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
	}

	renderer::~renderer()
	{

	}

	void renderer::submit(const mesh& mesh, const shader& shader)
	{
		m_draw_commands.emplace_back(std::cref(mesh), std::cref(shader));
	}

	void renderer::render_frame()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		for(const auto& [mesh, shader] : m_draw_commands)
		{
			glUseProgram(shader);
			glBindVertexArray(mesh);

			glDrawElements(GL_TRIANGLES, (GLsizei)mesh.indices.size(), GL_UNSIGNED_INT, nullptr);
		}

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
			log::error("OpenGL[{}]: {}", id, msg);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
		case GL_DEBUG_SEVERITY_LOW:
			log::warning("OpenGL[{}]: {}", id, msg);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			log::info("OpenGL[{}]: {}", id, msg);
			break;
		}
	}
}
