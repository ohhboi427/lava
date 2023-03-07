#include "pch.h"
#include "resource_manager.h"

namespace lava
{
	std::unordered_map<std::filesystem::path, std::weak_ptr<resource>> resource_manager::s_resources;
}
