#pragma once

#include <filesystem>
#include <unordered_map>

namespace lava
{
	class shader;

	class shader_library
	{
	public:
		shader_library() = delete;
		shader_library(const shader_library&) = delete;
		shader_library(shader_library&&) noexcept = delete;
		~shader_library() = delete;

		shader_library& operator=(const shader_library&) = delete;
		shader_library& operator=(shader_library&&) noexcept = delete;

		static void load_all(const std::filesystem::path& directory);
		static void load(const std::filesystem::path& path);
		static void purge_cache();

		static shader& get(const std::filesystem::path& path);

	private:
		static std::unordered_map<std::filesystem::path, shader*> s_shaders;

		static shader* compile(const std::filesystem::path& path);
	};
}
