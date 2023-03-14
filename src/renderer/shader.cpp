#include "pch.h"
#include "shader.h"

#include "../resource/resource_manager.h"
#include "../resource/text_file.h"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <nlohmann/json.hpp>

namespace lava
{
	namespace
	{
		enum class shader_stage : uint32_t
		{
			vertex = 35633u,
			fragment = 35632u,
		};

		std::string stage_to_str(shader_stage stage)
		{
			switch(stage)
			{
			case shader_stage::vertex:
				return "vertex";
			case shader_stage::fragment:
				return "fragment";
			}

			return "invalid";
		}
	}

	shader::shader(const std::filesystem::path& path)
		: resource(path)
	{
		compile();
		reflect();
	}

	shader::~shader()
	{
		glDeleteProgram(m_handle);
	}

	void shader::compile()
	{
		static constexpr std::array<shader_stage, 2u> s_stages =
		{
			shader_stage::vertex,
			shader_stage::fragment,
		};

		std::filesystem::path directory = m_path.parent_path();
		nlohmann::json shader_description = nlohmann::json::parse(std::ifstream(m_path));
		
		std::unordered_map<shader_stage, std::shared_ptr<text_file>> source_files;
		for(const auto& stage : s_stages)
		{
			source_files.insert({ stage, resource_manager::get<text_file>(directory / shader_description.at(stage_to_str(stage))) });
		}

		m_handle = glCreateProgram();

		std::vector<uint32_t> shaders;
		for(const auto& [stage, source] : source_files)
		{
			uint32_t& shader = shaders.emplace_back(glCreateShader((uint32_t)stage));

			const char* source_cstr = source->cdata().c_str();
			glShaderSource(shader, 1, &source_cstr, nullptr);

			glCompileShader(shader);

			glAttachShader(m_handle, shader);
		}

		glLinkProgram(m_handle);

		for(const auto& shader : shaders)
		{
			glDeleteShader(shader);
		}
	}

	void shader::reflect()
	{
		int32_t uniform_count;
		glGetProgramInterfaceiv(m_handle, GL_UNIFORM, GL_ACTIVE_RESOURCES, &uniform_count);

		uint32_t name_length_property = GL_NAME_LENGTH;
		for(uint32_t i = 0u; i < (uint32_t)uniform_count; i++)
		{
			int32_t name_length;
			glGetProgramResourceiv(m_handle, GL_UNIFORM, i, 1, &name_length_property, 1, nullptr, &name_length);

			std::string name((size_t)name_length - 1u, (char)0);
			glGetProgramResourceName(m_handle, GL_UNIFORM, i, name_length, nullptr, name.data());

			m_uniforms.insert({ name, glGetProgramResourceLocation(m_handle, GL_UNIFORM, name.c_str()) });
		}
	}

	void shader::set_int(const std::string& name, int32_t value)
	{
		glProgramUniform1i(m_handle, uniform_location(name), value);
	}

	void shader::set_int2(const std::string& name, const glm::ivec2& value)
	{
		glProgramUniform2iv(m_handle, uniform_location(name), 1, glm::value_ptr(value));
	}

	void shader::set_int3(const std::string& name, const glm::ivec3& value)
	{
		glProgramUniform3iv(m_handle, uniform_location(name), 1, glm::value_ptr(value));
	}

	void shader::set_int4(const std::string& name, const glm::ivec4& value)
	{
		glProgramUniform4iv(m_handle, uniform_location(name), 1, glm::value_ptr(value));
	}

	void shader::set_float(const std::string& name, float value)
	{
		glProgramUniform1f(m_handle, uniform_location(name), value);
	}

	void shader::set_float2(const std::string& name, const glm::vec2& value)
	{
		glProgramUniform2fv(m_handle, uniform_location(name), 1, glm::value_ptr(value));
	}

	void shader::set_float3(const std::string& name, const glm::vec3& value)
	{
		glProgramUniform3fv(m_handle, uniform_location(name), 1, glm::value_ptr(value));
	}

	void shader::set_float4(const std::string& name, const glm::vec4& value)
	{
		glProgramUniform4fv(m_handle, uniform_location(name), 1, glm::value_ptr(value));
	}

	void shader::set_float3x3(const std::string& name, const glm::mat3& value)
	{
		glProgramUniformMatrix3fv(m_handle, uniform_location(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void shader::set_float4x4(const std::string& name, const glm::mat4& value)
	{
		glProgramUniformMatrix4fv(m_handle, uniform_location(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	int32_t shader::uniform_location(const std::string& name) const
	{
		if(m_uniforms.contains(name))
		{
			return m_uniforms.at(name);
		}

		return -1;
	}
}
