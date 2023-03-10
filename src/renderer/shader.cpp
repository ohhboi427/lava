#include "pch.h"
#include "shader.h"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

namespace lava
{
	shader::shader(uint32_t handle)
		: m_handle(handle)
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

	shader::shader(const shader& other)
		: m_handle(other.m_handle), m_uniforms(other.m_uniforms)
	{}

	shader::shader(shader&& other) noexcept
		: m_handle(other.m_handle), m_uniforms(std::move(other.m_uniforms))
	{
		other.m_handle = 0u;
	}

	shader& shader::operator=(const shader& rhs)
	{
		m_handle = rhs.m_handle;
		m_uniforms = rhs.m_uniforms;

		return *this;
	}

	shader& shader::operator=(shader&& rhs) noexcept
	{
		m_handle = rhs.m_handle;
		m_uniforms = std::move(rhs.m_uniforms);

		rhs.m_handle = 0u;

		return *this;
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
