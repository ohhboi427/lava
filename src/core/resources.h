#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <future>
#include <cstdint>

namespace lava
{
	using resource_text_t = std::string;
	using resource_binary_t = std::vector<uint8_t>;

	class resources
	{
	public:
		resources() = delete;
		resources(const resources&) = delete;
		resources(resources&&) noexcept = delete;
		~resources() = delete;

		resources& operator=(const resources&) = delete;
		resources& operator=(resources&&) noexcept = delete;

		template<typename T>
		static T load(const std::filesystem::path& path);

		template<typename T>
		static std::future<T> load_async(const std::filesystem::path& path);

	private:
		static resource_text_t text_load_impl(const std::filesystem::path& path);
		static resource_binary_t binary_load_impl(const std::filesystem::path& path);
	};
}
