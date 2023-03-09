#pragma once

#include "resource.h"

#include <filesystem>
#include <string>

namespace lava
{
	class text_file : public resource
	{
	public:
		text_file(const std::filesystem::path& path);
		~text_file();

		std::string& data() { m_is_dirty = true; return m_data; }
		const std::string& cdata() const { return m_data; }

	private:
		std::string m_data;
		bool m_is_dirty = false;
	};
}
