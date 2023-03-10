#pragma once

#include "../resource/resource.h"

#include <filesystem>
#include <string>
#include <string_view>
#include <map>
#include <cstdint>

namespace lava
{
	enum class shader_stage : uint32_t
	{
		vertex = 35633u,
		fragment = 35632u,
	};

	class shader : public resource
	{
	public:
		shader(const std::filesystem::path& path);
		~shader();

		operator uint32_t () const { return m_handle; }

	private:
		uint32_t m_handle;

		static std::filesystem::path stage_to_extension(shader_stage stage);
	};
}
