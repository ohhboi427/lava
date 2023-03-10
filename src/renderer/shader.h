#pragma once

#include <string>
#include <cstdint>

namespace lava
{
	class shader_library;

	class shader
	{
		friend class shader_library;

	public:
		shader(const shader& other);
		shader(shader&& other) noexcept;

		shader& operator=(const shader& rhs);
		shader& operator=(shader&& rhs) noexcept;

		operator uint32_t () const { return m_handle; }

	private:
		uint32_t m_handle;

		shader(uint32_t handle);
	};
}
