#include "pch.h"
#include "resource.h"

namespace lava
{
	resource::resource(const std::filesystem::path& path)
		: m_path(path)
	{}

	resource::~resource()
	{}
}
