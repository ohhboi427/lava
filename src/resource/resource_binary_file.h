#pragma once

#include <filesystem>
#include <vector>
#include <cstdint>

#include "resource.h"

namespace lava
{
	class resource_bin_file : public resource
	{
	public:
		resource_bin_file(const std::filesystem::path& path);
		~resource_bin_file();

		std::vector<uint8_t>& data() { m_isDirty = true; return m_data; }
		const std::vector<uint8_t>& cdata() const { return m_data; }

	private:
		std::vector<uint8_t> m_data;
		bool m_isDirty = false;
	};
}
