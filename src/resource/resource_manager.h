#pragma once

#include "../utility/concepts.h"

#include "resource.h"

#include <filesystem>
#include <memory>
#include <unordered_map>

namespace lava
{
	namespace resource_manager
	{
		namespace detail
		{
			extern std::unordered_map<std::filesystem::path, std::weak_ptr<resource>> s_resources;
		}

		template<typename T>
		static std::shared_ptr<T> get(const std::filesystem::path& path) requires (std::is_base_of_v<resource, T>)
		{
			if(detail::s_resources.contains(path) && !(detail::s_resources.at(path).expired()))
			{
				return std::dynamic_pointer_cast<T>(detail::s_resources.at(path).lock());
			}

			std::shared_ptr<T> new_resource = std::make_shared<T>(path);
			detail::s_resources.insert_or_assign(path, std::dynamic_pointer_cast<resource>(new_resource));

			return new_resource;
		}
	};
}
