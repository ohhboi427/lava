#pragma once

#include <glm/glm.hpp>

#include <string>
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
		void set_uniform(const std::string& name, const glm::ivec2& value);
		void set_uniform(const std::string& name, const glm::ivec3& value);
		void set_uniform(const std::string& name, const glm::ivec4& value);
		void set_uniform(const std::string& name, float value);
		void set_uniform(const std::string& name, const glm::vec2& value);
		void set_uniform(const std::string& name, const glm::vec3& value);
		void set_uniform(const std::string& name, const glm::vec4& value);
		void set_uniform(const std::string& name, const glm::mat3& value);
		void set_uniform(const std::string& name, const glm::mat4& value);

	private:
		uint32_t m_handle;
		std::unordered_map<std::string, int32_t> m_uniforms;

		shader(uint32_t handle);

		int32_t uniform_location(const std::string& name) const;
	};
}
