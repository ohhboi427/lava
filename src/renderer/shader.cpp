#include "pch.h"
#include "shader.h"

namespace lava
{
	shader::shader(uint32_t handle)
		: m_handle(handle)
	{}

	shader::shader(const shader& other)
		: m_handle(other.m_handle)
	{}

	shader::shader(shader&& other) noexcept
		: m_handle(other.m_handle)
	{
		other.m_handle = 0u;
	}

	shader& shader::operator=(const shader& rhs)
	{
		m_handle = rhs.m_handle;

		return *this;
	}

	shader& shader::operator=(shader&& rhs) noexcept
	{
		m_handle = rhs.m_handle;

		rhs.m_handle = 0u;

		return *this;
	}
}
