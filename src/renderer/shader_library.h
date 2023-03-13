#pragma once

#include <filesystem>
#include <unordered_map>

namespace lava
{
	class shader;

	namespace shader_library
	{
		void load_all(const std::filesystem::path& directory);
		void load(const std::filesystem::path& path);
		void purge_cache();

		shader& get(const std::filesystem::path& path);
	};
}
