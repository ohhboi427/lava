#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
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

		void set_uniform(const std::string& name, int32_t value);
		void set_uniform(const std::string& name, float value);

	private:
		uint32_t m_handle;
		std::unordered_map<std::string, int32_t> m_uniforms;

		shader(uint32_t handle);

		int32_t uniform_location(const std::string& name) const;
	};
}
