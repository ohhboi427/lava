#pragma once

#include <cstdint>

namespace lava
{
	enum class buffer_usage : uint32_t
	{
		stream_draw = 35040,
		stream_read = 35041,
		stream_copy = 35042,
		static_draw = 35044,
		static_read = 35045,
		static_copy = 35046,
		dynamic_draw = 35048,
		dynamic_read = 35049,
		dynamic_copy = 35050,
	};

	class buffer
	{
	public:
		buffer();
		buffer(const void* data, int64_t size, buffer_usage usage);
		buffer(const buffer&) = delete;
		buffer(buffer&&) noexcept = delete;
		~buffer();

		buffer& operator=(const buffer&) = delete;
		buffer& operator=(buffer&&) noexcept = delete;

		operator uint32_t () const { return m_handle; }

		void set_data(const void* data, int64_t size, buffer_usage usage);
		void set_sub_data(const void* data, int64_t size, int64_t offset);

	private:
		uint32_t m_handle;
	};
}
