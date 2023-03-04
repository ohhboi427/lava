#include "pch.h"
#include "resources.h"

namespace lava
{
	resource_text_t resources::text_load_impl(const std::filesystem::path& path)
	{
		resource_text_t result;

		std::ifstream file(path, std::ios::in | std::ios::binary);
		if(file)
		{
			file.seekg(0, std::ios::end);
			size_t length = file.tellg();

			if(length != -1)
			{
				result.resize(length);
				file.seekg(0, std::ios::beg);
				file.read(result.data(), length);
			}
		}

		return result;
	}

	template<>
	resource_text_t resources::load(const std::filesystem::path& path)
	{
		return text_load_impl(path);
	}

	template<>
	std::future<resource_text_t> resources::load_async(const std::filesystem::path& path)
	{
		return std::async(std::launch::async, text_load_impl, path);
	}

	resource_binary_t resources::binary_load_impl(const std::filesystem::path& path)
	{
		resource_binary_t result;

		std::ifstream file(path, std::ios::in | std::ios::binary);
		if(file)
		{
			file.seekg(0, std::ios::end);
			size_t length = file.tellg();

			if(length != -1)
			{
				result.resize(length);
				file.seekg(0, std::ios::beg);
				file.read((char*)result.data(), length);
			}
		}

		return result;
	}

	template<>
	resource_binary_t resources::load(const std::filesystem::path& path)
	{
		return binary_load_impl(path);
	}

	template<>
	std::future<resource_binary_t> resources::load_async(const std::filesystem::path& path)
	{
		return std::async(std::launch::async, binary_load_impl, path);
	}
}
