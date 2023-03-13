#include "pch.h"
#include "buffer.h"

#include <glad/gl.h>

namespace lava
{
	buffer::buffer()
	{
		glCreateBuffers(1, &m_handle);
	}

	buffer::buffer(const void* data, int64_t size, buffer_usage usage)
		: buffer()
	{
		set_data(data, size, usage);
	}

	buffer::~buffer()
	{
		glDeleteBuffers(1, &m_handle);
	}

	void buffer::set_data(const void* data, int64_t size, buffer_usage usage)
	{
		glNamedBufferData(m_handle, size, data, (GLenum)usage);
	}

	void buffer::set_sub_data(const void* data, int64_t size, int64_t offset)
	{
		glNamedBufferSubData(m_handle, offset, size, data);
	}
}
