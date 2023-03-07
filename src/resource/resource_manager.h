#pragma once

#include "resource.h"

#include <memory>
#include <filesystem>
#include <type_traits>
#include <unordered_map>

namespace lava
{
	template<typename T>
	concept resource_base = std::is_base_of<resource, T>::value;

	class resource_manager
	{
	public:
		resource_manager() = delete;
		resource_manager(const resource_manager&) = delete;
		resource_manager(resource_manager&&) noexcept = delete;
		~resource_manager() = delete;

		resource_manager& operator=(const resource_manager&) = delete;
		resource_manager& operator=(resource_manager&&) noexcept = delete;

		template<resource_base T>
		static std::shared_ptr<T> get(const std::filesystem::path& path)
		{
			if(s_resources.contains(path) && !(s_resources.at(path).expired()))
			{
				return std::dynamic_pointer_cast<T>(s_resources.at(path).lock());
			}

			std::shared_ptr<T> newResource = std::make_shared<T>(path);
			s_resources.insert_or_assign(path, std::dynamic_pointer_cast<resource>(newResource));

			return newResource;
		}

	private:
		static std::unordered_map<std::filesystem::path, std::weak_ptr<resource>> s_resources;
	};
}
