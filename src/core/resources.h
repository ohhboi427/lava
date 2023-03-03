#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <future>
#include <cstdint>

namespace lava
{
	using resource_text = std::string;
	using resource_binary = std::vector<uint8_t>;

	class resources
	{
	public:
		template<typename T>
		static T load(const std::filesystem::path& path);

		template<typename T>
		static std::future<T> load_async(const std::filesystem::path& path);

	private:
		static resource_text text_load_impl(const std::filesystem::path& path);
		static resource_binary binary_load_impl(const std::filesystem::path& path);
	};
}
