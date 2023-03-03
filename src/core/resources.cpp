#include "pch.h"
#include "resources.h"

namespace lava
{
	resource_text resources::text_load_impl(const std::filesystem::path& path)
	{
		resource_text result;

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
	resource_text resources::load(const std::filesystem::path& path)
	{
		return text_load_impl(path);
	}

	template<>
	std::future<resource_text> resources::load_async(const std::filesystem::path& path)
	{
		return std::async(std::launch::async, text_load_impl, path);
	}

	resource_binary resources::binary_load_impl(const std::filesystem::path& path)
	{
		resource_binary result;

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
	resource_binary resources::load(const std::filesystem::path& path)
	{
		return binary_load_impl(path);
	}

	template<>
	std::future<resource_binary> resources::load_async(const std::filesystem::path& path)
	{
		return std::async(std::launch::async, binary_load_impl, path);
	}
}
