#pragma once

#include "resource.h"

#include <filesystem>
#include <string>

namespace lava
{
	class resource_text_file : public resource
	{
	public:
		resource_text_file(const std::filesystem::path& path);
		~resource_text_file();

		std::string& data() { m_isDirty = true; return m_data; }
		const std::string& cdata() const { return m_data; }

	private:
		std::string m_data;
		bool m_isDirty = false;
	};
}
