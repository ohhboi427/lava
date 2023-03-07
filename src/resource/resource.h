#pragma once

#include <filesystem>

namespace lava
{
	class resource
	{
	public:
		resource(const std::filesystem::path& path);
		resource(const resource&) = delete;
		resource(resource&&) noexcept = delete;
		virtual ~resource();

		resource& operator=(const resource&) = delete;
		resource& operator=(resource&&) noexcept = delete;

		const std::filesystem::path& path() const { return m_path; }

	protected:
		std::filesystem::path m_path;
	};
}
