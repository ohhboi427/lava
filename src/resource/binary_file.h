#pragma once

#include <filesystem>
#include <vector>
#include <cstdint>

#include "resource.h"

namespace lava
{
	class binary_file : public resource
	{
	public:
		binary_file(const std::filesystem::path& path);
		~binary_file();

		std::vector<uint8_t>& data() { m_is_dirty = true; return m_data; }
		const std::vector<uint8_t>& cdata() const { return m_data; }

	private:
		std::vector<uint8_t> m_data;
		bool m_is_dirty = false;
	};
}
