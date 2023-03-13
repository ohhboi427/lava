#pragma once

#include "../resource/resource.h"

#include <glm/glm.hpp>

#include <filesystem>
#include <string>
#include <unordered_map>
#include <cstdint>

namespace lava
{
	class shader : public resource
	{
	public:
		shader(const std::filesystem::path& path);
		~shader();

		operator uint32_t () const { return m_handle; }

		void set_int(const std::string& name, int32_t value);
		void set_int2(const std::string& name, const glm::ivec2& value);
		void set_int3(const std::string& name, const glm::ivec3& value);
		void set_int4(const std::string& name, const glm::ivec4& value);
		void set_float(const std::string& name, float value);
		void set_float2(const std::string& name, const glm::vec2& value);
		void set_float3(const std::string& name, const glm::vec3& value);
		void set_float4(const std::string& name, const glm::vec4& value);
		void set_float3x3(const std::string& name, const glm::mat3& value);
		void set_float4x4(const std::string& name, const glm::mat4& value);

	private:
		uint32_t m_handle;
		std::unordered_map<std::string, int32_t> m_uniforms;

		int32_t uniform_location(const std::string& name) const;

		void compile();
		void reflect();
	};
}
