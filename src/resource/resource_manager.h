#pragma once

#include "../utility/concepts.h"

#include "resource.h"

#include <filesystem>
#include <memory>
#include <unordered_map>

namespace lava
{
	class resource_manager
	{
	public:
		resource_manager() = delete;
		resource_manager(const resource_manager&) = delete;
		resource_manager(resource_manager&&) noexcept = delete;
		~resource_manager() = delete;

		resource_manager& operator=(const resource_manager&) = delete;
		resource_manager& operator=(resource_manager&&) noexcept = delete;

		template<typename T>
		static std::shared_ptr<T> get(const std::filesystem::path& path) requires (std::is_base_of_v<resource, T>)
		{
			if(s_resources.contains(path) && !(s_resources.at(path).expired()))
			{
				return std::dynamic_pointer_cast<T>(s_resources.at(path).lock());
			}

			std::shared_ptr<T> new_resource = std::make_shared<T>(path);
			s_resources.insert_or_assign(path, std::dynamic_pointer_cast<resource>(new_resource));

			return new_resource;
		}

	private:
		static std::unordered_map<std::filesystem::path, std::weak_ptr<resource>> s_resources;
	};
}
